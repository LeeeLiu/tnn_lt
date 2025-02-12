// Tencent is pleased to support the open source community by making TNN available.
//
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#include "worker.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "tnn/core/macro.h"
#include "tnn/core/status.h"

#include "ultra_face_detector.h"
#include "blazeface_detector.h"
#include "youtu_face_align.h"
#include "face_detect_aligner.h"
#include "tnn_fps_counter.h"

#include "macro.h"
#include "utils/utils.h"


using TNN_NS::TNN_OK;

std::shared_ptr<TNN_NS::YoutuFaceAlign> CreateBlazeFaceAlign(std::string modelPath,
                           int width, int height, int topk,
                           TNN_NS::TNNComputeUnits computUnitType, int phase) {

    auto predictor = std::make_shared<TNN_NS::YoutuFaceAlign>();
    std::string proto_content, model_content, lib_path = "";
    if(phase == 1) {
        proto_content = fdLoadFile(modelPath + "/youtu_face_alignment_phase1.tnnproto");
        model_content = fdLoadFile(modelPath + "/youtu_face_alignment_phase1.tnnmodel");
    } else if(phase == 2) {
        proto_content = fdLoadFile(modelPath + "/youtu_face_alignment_phase2.tnnproto");
        model_content = fdLoadFile(modelPath + "/youtu_face_alignment_phase2.tnnmodel");
    }

    auto option = std::make_shared<TNN_NS::YoutuFaceAlignOption>();
    option->proto_content = proto_content;
    option->model_content = model_content;
    option->face_threshold = 0.5;
    option->min_face_size = 20;
    option->phase = phase;
    option->input_width = width;
    option->input_height = height;
    option->net_scale = phase == 1? 1.2 : 1.3;
    std::string mean_file_path = phase==1?  modelPath + "/youtu_mean_pts_phase1.txt" :  modelPath + "/youtu_mean_pts_phase2.txt";
    option->mean_pts_path = std::move(mean_file_path);
    option->compute_units = computUnitType;

    auto status = predictor->Init(option);
    if (status != TNN_OK) {
        LOGE("align init failed %d %s", (int) status, status.description().c_str());
        return nullptr;
    }
    return predictor;
}

Status Worker::Init(std::string model_path) {
    fps_counter_ = std::make_shared<TNNFPSCounter>();

    // Init FaceDetector
    auto proto_content = fdLoadFile(model_path+"/face_detector/version-slim-320_simplified.tnnproto");
    auto model_content = fdLoadFile(model_path+"/face_detector/version-slim-320_simplified.tnnmodel");

    // if enable openvino, set computUnitType to TNNComputeUnitsOpenvino
    TNN_NS::TNNComputeUnits computUnitType = TNN_NS::TNNComputeUnitsCPU;
#ifdef _CUDA_
    computUnitType = TNN_NS::TNNComputeUnitsTensorRT;
#elif _OPENVINO_
    computUnitType = TNN_NS::TNNComputeUnitsOpenvino;
#endif

    auto option = std::make_shared<TNN_NS::UltraFaceDetectorOption>();
    {
        option->proto_content = proto_content;
        option->model_content = model_content;
        option->library_path = "";
        option->compute_units = computUnitType;
        option->score_threshold = 0.95;
        option->iou_threshold = 0.15;
    }
    
    detecotr_ = std::make_shared<TNN_NS::UltraFaceDetector>();
    CHECK_TNN_STATUS(detecotr_->Init(option));

    // Init BlazeFaceDetector
    int height = 128;
    int width  = 128;
    int topk = 5; 

    auto blaze_detector_proto_content = fdLoadFile(model_path+"/blazeface/blazeface.tnnproto");
    auto blaze_detector_model_content = fdLoadFile(model_path+"/blazeface/blazeface.tnnmodel");
    auto blaze_detector_option = std::make_shared<TNN_NS::BlazeFaceDetectorOption>();
    {
        blaze_detector_option->proto_content = blaze_detector_proto_content;
        blaze_detector_option->model_content = blaze_detector_model_content;
        blaze_detector_option->library_path = "";
        blaze_detector_option->compute_units = computUnitType;
        blaze_detector_option->min_suppression_threshold = 0.3;
        blaze_detector_option->anchor_path = model_path + "/blazeface/blazeface_anchors.txt";
    }

    blaze_detecotr_ = std::make_shared<TNN_NS::BlazeFaceDetector>();
    CHECK_TNN_STATUS(blaze_detecotr_->Init(blaze_detector_option));


    // Init aligner
    aligner_ = std::make_shared<TNN_NS::FaceDetectAligner>();

    auto predictor_phase1 = CreateBlazeFaceAlign(model_path + "/youtu_face_alignment",
                                                 width, height, topk,
                                                 computUnitType, 1);
    if(predictor_phase1 == nullptr) {
        LOGE("create align phase1 failed \n");
        return -1;
    }

    auto predictor_phase2 = CreateBlazeFaceAlign(model_path + "/youtu_face_alignment",
                                                 width, height, topk,
                                                 computUnitType, 2);
    if(predictor_phase2 == nullptr) {
        LOGE("create align phase2 failed \n");
        return -1;
    }

    CHECK_TNN_STATUS(aligner_->Init({blaze_detecotr_, predictor_phase1, predictor_phase2}));
    
    return TNN_OK;
};

Status Worker::DrawUI(cv::Mat &frame) {
    // FPS
    char fps_char[200];
    snprintf(fps_char, 200, "FPS:%3.0f", fps_counter_->GetFPS("frame"));
    std::string text(fps_char);
    int font_face = cv::FONT_HERSHEY_COMPLEX; 
    double font_scale = 1.2;
    int thickness = 2;
    int baseline;
    cv::Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &baseline);
 
    cv::Point origin; 
    origin.x = 10;
    origin.y = 10 + text_size.height;
    //cv::putText(frame, text, origin, font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 8, 0);

    // CMD
    std::vector<std::string> sentences = {
        // // "a: toggle facealign",
        // "d: toggle facedetect",
        "c: quit",
        "Press:",
    };
    font_scale = 0.5;
    thickness = 1;
    origin.x = 10;
    origin.y = frame.rows;
    for(auto str : sentences) {
        text_size = cv::getTextSize(str, font_face, font_scale, thickness, &baseline);
        origin.y -= text_size.height + 5;
        cv::putText(frame, str, origin, font_face, font_scale, cv::Scalar(0, 0, 255), thickness, 8, 0);
    }
    return TNN_OK;
}

Status Worker::FaceDetectWithPaint(cv::Mat &frame, cv::Mat &frame_paint) {
    //prepare input
    std::vector<int> nchw = {1, frame.channels(), frame.rows, frame.cols};
    auto image_mat = std::make_shared<TNN_NS::Mat>(TNN_NS::DEVICE_NAIVE, TNN_NS::N8UC3, nchw, frame.data);

    //Predict
    std::shared_ptr<TNN_NS::TNNSDKOutput> sdk_output = detecotr_->CreateSDKOutput();
    CHECK_TNN_STATUS(detecotr_->Predict(std::make_shared<TNN_NS::UltraFaceDetectorInput>(image_mat), sdk_output));

    std::vector<TNN_NS::FaceInfo> face_info;
    if (sdk_output && dynamic_cast<TNN_NS::UltraFaceDetectorOutput *>(sdk_output.get())) {
        auto face_output = dynamic_cast<TNN_NS::UltraFaceDetectorOutput *>(sdk_output.get());
        face_info = face_output->face_list;
    }

    const int image_orig_height = nchw[2];
    const int image_orig_width  = nchw[3];
    const int h = detecotr_->GetInputShape()[2];
    const int w = detecotr_->GetInputShape()[3];

    for (int i = 0; i < face_info.size(); i++) {
        auto face = face_info[i].AdjustToViewSize(image_orig_height, image_orig_width, 2);
        cv::Point top_left(face.x1, face.y1);
        cv::Point bottom_right(face.x2, face.y2);
        cv::rectangle(frame_paint, top_left, bottom_right, cv::Scalar(0, 255, 127));
    }

    return TNN_OK;
};

Status Worker::BlazeFaceDetectWithPaint(cv::Mat &frame, cv::Mat &frame_paint) {
    std::vector<int> nchw = {1, frame.channels(), frame.rows, frame.cols};
    auto image_mat = std::make_shared<TNN_NS::Mat>(TNN_NS::DEVICE_NAIVE, TNN_NS::N8UC3, nchw, frame.data);

    //Predict
    std::shared_ptr<TNN_NS::TNNSDKOutput> sdk_output = blaze_detecotr_->CreateSDKOutput();
    CHECK_TNN_STATUS(blaze_detecotr_->Predict(std::make_shared<TNN_NS::BlazeFaceDetectorInput>(image_mat), sdk_output));

    std::vector<TNN_NS::BlazeFaceInfo> face_info;
    if (sdk_output && dynamic_cast<TNN_NS::BlazeFaceDetectorOutput *>(sdk_output.get())) {
        auto face_output = dynamic_cast<TNN_NS::BlazeFaceDetectorOutput *>(sdk_output.get());
        face_info = face_output->face_list;
    }

    const int image_orig_height = nchw[2];
    const int image_orig_width  = nchw[3];
    const int h = blaze_detecotr_->GetInputShape()[2];
    const int w = blaze_detecotr_->GetInputShape()[3];

    for (int i = 0; i < face_info.size(); i++) {
        auto face = face_info[i].AdjustToViewSize(image_orig_height, image_orig_width, 2);
        cv::Point top_left(face.x1, face.y1);
        cv::Point bottom_right(face.x2, face.y2);
        cv::rectangle(frame_paint, top_left, bottom_right, cv::Scalar(0, 255, 0));
    }

    return TNN_OK;
};

//static int flag_init = 0;
 double left_mean_x ;
 double left_mean_y ;
 double right_mean_x ;
 double right_mean_y;
	
Status Worker::AlignWithPaint(int index, cv::Mat &frame, cv::Mat &frame_paint) {
    std::vector<int> nchw = {1, frame.channels(), frame.rows, frame.cols};
    auto image_mat = std::make_shared<TNN_NS::Mat>(TNN_NS::DEVICE_NAIVE, TNN_NS::N8UC3, nchw, frame.data);

    //Predict
    std::shared_ptr<TNN_NS::TNNSDKOutput> sdk_output = aligner_->CreateSDKOutput();
    CHECK_TNN_STATUS(aligner_->Predict(std::make_shared<TNN_NS::TNNSDKInput>(image_mat), sdk_output));

    TNN_NS::YoutuFaceAlignInfo face_info;
    if (sdk_output && dynamic_cast<TNN_NS::YoutuFaceAlignOutput *>(sdk_output.get())) {
        auto face_output = dynamic_cast<TNN_NS::YoutuFaceAlignOutput *>(sdk_output.get());
        face_info = face_output->face;
    }

    const int image_orig_height = nchw[2];
    const int image_orig_width  = nchw[3];

    auto face = face_info.AdjustToViewSize(image_orig_height, image_orig_width, 2);

	int len = face.key_points.size();
	//printf("len=%d",len);
	for(int i = 0; i< len; i++) {
		auto xy = face.key_points[i];
		//if(i>15 && i<32)
		//if(i>148 && i<197)
		//if(i>268 && i<275)

		bool flag1 = ( i==269 || i==270 ); // 瞳孔
		bool flag2 = ( i==16 || i==18 || i==20 || i==22 || i==24 || i==26 || i==28 || i==30 );

		if( flag1 || flag2 )
		//if(i>148 && i<197)
			cv::circle(frame_paint, cv::Point(xy.first, xy.second), 2, cv::Scalar( 0, 128, 255 ), cv::FILLED, cv::LINE_8);
    }

	//if (flag_init==0){
		left_mean_x = (face.key_points[22].first + face.key_points[18].first)/2;
		left_mean_y = (face.key_points[16].second + face.key_points[20].second)/2;
		//left_mean_y = (face.key_points[22].second + face.key_points[18].second)/2;

		right_mean_x = (face.key_points[30].first + face.key_points[26].first)/2;
		right_mean_y = (face.key_points[28].second + face.key_points[24].second)/2;
		//right_mean_y = (face.key_points[30].second + face.key_points[26].second)/2;

		//flag_init = 1;
	//}

	double left_delta_x = face.key_points[269].first - left_mean_x;
	double left_delta_y = face.key_points[269].second - left_mean_y;
	double right_delta_x = face.key_points[270].first - right_mean_x;
	double right_delta_y = face.key_points[270].second - right_mean_y;
	double focal_distance = 50;

	// 特殊处理：向下看，上眼皮会下垂
	double scale_fac = 3.0;
	// left_d: 上下眼睑  距离
	double left_height = (face.key_points[20].first - face.key_points[16].first) / 2 ;
	double left_d = face.key_points[18].second - face.key_points[22].second;
	if  (  left_d < left_height/2   )
		left_delta_y = left_height/2 - left_d + 3;

	// right_d: 上下眼睑  距离
	double right_height = (face.key_points[24].first - face.key_points[28].first) / 2 ;
	double right_d = face.key_points[26].second - face.key_points[30].second;
	if  (  right_d < right_height/2   )
		right_delta_y = right_height/2 - right_d + 3;

	/*
	// debug
	std::ofstream txt_writer3("./video/debug.txt", std::ios::app);
	txt_writer3 <<left_d<<" "<<left_height/2<<"\t"<<right_d<<" "<<right_height/2<< std::endl;
	txt_writer3.close(); 
	*/

	double Left_Yaw    = atan (left_delta_x/ focal_distance);
	double Left_Pitch  = atan (left_delta_y/ focal_distance);
	double Right_Yaw   = atan (right_delta_x/ focal_distance);
	double Right_Pitch = atan (right_delta_y/ focal_distance);

/*
	//std::ofstream txt_writer1("./video/delta_x_y.txt", std::ios::app);  //在<fstream>库中
	//txt_writer1 <<left_delta_x<<" "<<left_delta_y<<"\t"<<right_delta_x<<" "<<right_delta_y<< std::endl;
	//txt_writer1.close();
*/

	char path[50];
	snprintf(path, 50, "./video/YawPitch/%d.txt", index);
	std::ofstream txt_writer2(path);
	txt_writer2 <<Left_Yaw<<" "<<Left_Pitch<<"\t"<<Right_Yaw<<" "<<Right_Pitch<< std::endl;
	txt_writer2.close();  

    return TNN_OK;
};


Status GetROI(cv::Mat &frame, cv::Rect &roi) {
    float origin_h = (float)frame.rows;
    float origin_w = (float)frame.cols;
    float max_ratio = 1.1;
    float max_width = max_ratio * origin_h;
    int x, y, w, h;
    roi.x = 0;
    roi.y = 0;
    roi.width  = origin_w;
    roi.height = origin_h;
    if ( origin_w > max_width ) {
        roi.x = (origin_w - max_width) / 2.0;
        roi.width = max_width;
    }
    return TNN_OK;
}

Status Worker::FrocessFrame(int index, cv::Mat &frame, cv::Mat &frame_paint) {
    fps_counter_->Begin("frame");

    cv::Rect roi;
    RETURN_ON_NEQ(GetROI(frame, roi), TNN_OK);
    cv::Mat frame_croped = frame(roi).clone();
    cv::Mat frame_paint_croped = frame_paint(roi);

    RETURN_ON_NEQ(FaceDetectWithPaint(frame, frame_paint), TNN_OK);
    // RETURN_ON_NEQ(BlazeFaceDetectWithPaint(frame_croped, frame_paint_croped), TNN_OK);
    RETURN_ON_NEQ(AlignWithPaint(index, frame_croped, frame_paint_croped), TNN_OK);

    fps_counter_->End("frame");
    RETURN_ON_NEQ(DrawUI(frame_paint), TNN_OK);
    return TNN_OK; 
}
