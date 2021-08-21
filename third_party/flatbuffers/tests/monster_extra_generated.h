// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_MONSTEREXTRA_MYGAME_H_
#define FLATBUFFERS_GENERATED_MONSTEREXTRA_MYGAME_H_

#include "flatbuffers/flatbuffers.h"

namespace MyGame {

struct MonsterExtra;
struct MonsterExtraBuilder;
struct MonsterExtraT;

bool operator==(const MonsterExtraT &lhs, const MonsterExtraT &rhs);
bool operator!=(const MonsterExtraT &lhs, const MonsterExtraT &rhs);

inline const flatbuffers::TypeTable *MonsterExtraTypeTable();

struct MonsterExtraT : public flatbuffers::NativeTable {
  typedef MonsterExtra TableType;
  double d0 = std::numeric_limits<double>::quiet_NaN();
  double d1 = std::numeric_limits<double>::quiet_NaN();
  double d2 = std::numeric_limits<double>::infinity();
  double d3 = -std::numeric_limits<double>::infinity();
  float f0 = std::numeric_limits<float>::quiet_NaN();
  float f1 = std::numeric_limits<float>::quiet_NaN();
  float f2 = std::numeric_limits<float>::infinity();
  float f3 = -std::numeric_limits<float>::infinity();
  std::vector<double> dvec{};
  std::vector<float> fvec{};
};

inline bool operator==(const MonsterExtraT &lhs, const MonsterExtraT &rhs) {
  return
      (lhs.d0 == rhs.d0) &&
      (lhs.d1 == rhs.d1) &&
      (lhs.d2 == rhs.d2) &&
      (lhs.d3 == rhs.d3) &&
      (lhs.f0 == rhs.f0) &&
      (lhs.f1 == rhs.f1) &&
      (lhs.f2 == rhs.f2) &&
      (lhs.f3 == rhs.f3) &&
      (lhs.dvec == rhs.dvec) &&
      (lhs.fvec == rhs.fvec);
}

inline bool operator!=(const MonsterExtraT &lhs, const MonsterExtraT &rhs) {
    return !(lhs == rhs);
}


struct MonsterExtra FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef MonsterExtraT NativeTableType;
  typedef MonsterExtraBuilder Builder;
  static const flatbuffers::TypeTable *MiniReflectTypeTable() {
    return MonsterExtraTypeTable();
  }
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_D0 = 4,
    VT_D1 = 6,
    VT_D2 = 8,
    VT_D3 = 10,
    VT_F0 = 12,
    VT_F1 = 14,
    VT_F2 = 16,
    VT_F3 = 18,
    VT_DVEC = 20,
    VT_FVEC = 22
  };
  double d0() const {
    return GetField<double>(VT_D0, std::numeric_limits<double>::quiet_NaN());
  }
  bool mutate_d0(double _d0) {
    return SetField<double>(VT_D0, _d0, std::numeric_limits<double>::quiet_NaN());
  }
  double d1() const {
    return GetField<double>(VT_D1, std::numeric_limits<double>::quiet_NaN());
  }
  bool mutate_d1(double _d1) {
    return SetField<double>(VT_D1, _d1, std::numeric_limits<double>::quiet_NaN());
  }
  double d2() const {
    return GetField<double>(VT_D2, std::numeric_limits<double>::infinity());
  }
  bool mutate_d2(double _d2) {
    return SetField<double>(VT_D2, _d2, std::numeric_limits<double>::infinity());
  }
  double d3() const {
    return GetField<double>(VT_D3, -std::numeric_limits<double>::infinity());
  }
  bool mutate_d3(double _d3) {
    return SetField<double>(VT_D3, _d3, -std::numeric_limits<double>::infinity());
  }
  float f0() const {
    return GetField<float>(VT_F0, std::numeric_limits<float>::quiet_NaN());
  }
  bool mutate_f0(float _f0) {
    return SetField<float>(VT_F0, _f0, std::numeric_limits<float>::quiet_NaN());
  }
  float f1() const {
    return GetField<float>(VT_F1, std::numeric_limits<float>::quiet_NaN());
  }
  bool mutate_f1(float _f1) {
    return SetField<float>(VT_F1, _f1, std::numeric_limits<float>::quiet_NaN());
  }
  float f2() const {
    return GetField<float>(VT_F2, std::numeric_limits<float>::infinity());
  }
  bool mutate_f2(float _f2) {
    return SetField<float>(VT_F2, _f2, std::numeric_limits<float>::infinity());
  }
  float f3() const {
    return GetField<float>(VT_F3, -std::numeric_limits<float>::infinity());
  }
  bool mutate_f3(float _f3) {
    return SetField<float>(VT_F3, _f3, -std::numeric_limits<float>::infinity());
  }
  const flatbuffers::Vector<double> *dvec() const {
    return GetPointer<const flatbuffers::Vector<double> *>(VT_DVEC);
  }
  flatbuffers::Vector<double> *mutable_dvec() {
    return GetPointer<flatbuffers::Vector<double> *>(VT_DVEC);
  }
  const flatbuffers::Vector<float> *fvec() const {
    return GetPointer<const flatbuffers::Vector<float> *>(VT_FVEC);
  }
  flatbuffers::Vector<float> *mutable_fvec() {
    return GetPointer<flatbuffers::Vector<float> *>(VT_FVEC);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<double>(verifier, VT_D0) &&
           VerifyField<double>(verifier, VT_D1) &&
           VerifyField<double>(verifier, VT_D2) &&
           VerifyField<double>(verifier, VT_D3) &&
           VerifyField<float>(verifier, VT_F0) &&
           VerifyField<float>(verifier, VT_F1) &&
           VerifyField<float>(verifier, VT_F2) &&
           VerifyField<float>(verifier, VT_F3) &&
           VerifyOffset(verifier, VT_DVEC) &&
           verifier.VerifyVector(dvec()) &&
           VerifyOffset(verifier, VT_FVEC) &&
           verifier.VerifyVector(fvec()) &&
           verifier.EndTable();
  }
  MonsterExtraT *UnPack(const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(MonsterExtraT *_o, const flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static flatbuffers::Offset<MonsterExtra> Pack(flatbuffers::FlatBufferBuilder &_fbb, const MonsterExtraT* _o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct MonsterExtraBuilder {
  typedef MonsterExtra Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_d0(double d0) {
    fbb_.AddElement<double>(MonsterExtra::VT_D0, d0, std::numeric_limits<double>::quiet_NaN());
  }
  void add_d1(double d1) {
    fbb_.AddElement<double>(MonsterExtra::VT_D1, d1, std::numeric_limits<double>::quiet_NaN());
  }
  void add_d2(double d2) {
    fbb_.AddElement<double>(MonsterExtra::VT_D2, d2, std::numeric_limits<double>::infinity());
  }
  void add_d3(double d3) {
    fbb_.AddElement<double>(MonsterExtra::VT_D3, d3, -std::numeric_limits<double>::infinity());
  }
  void add_f0(float f0) {
    fbb_.AddElement<float>(MonsterExtra::VT_F0, f0, std::numeric_limits<float>::quiet_NaN());
  }
  void add_f1(float f1) {
    fbb_.AddElement<float>(MonsterExtra::VT_F1, f1, std::numeric_limits<float>::quiet_NaN());
  }
  void add_f2(float f2) {
    fbb_.AddElement<float>(MonsterExtra::VT_F2, f2, std::numeric_limits<float>::infinity());
  }
  void add_f3(float f3) {
    fbb_.AddElement<float>(MonsterExtra::VT_F3, f3, -std::numeric_limits<float>::infinity());
  }
  void add_dvec(flatbuffers::Offset<flatbuffers::Vector<double>> dvec) {
    fbb_.AddOffset(MonsterExtra::VT_DVEC, dvec);
  }
  void add_fvec(flatbuffers::Offset<flatbuffers::Vector<float>> fvec) {
    fbb_.AddOffset(MonsterExtra::VT_FVEC, fvec);
  }
  explicit MonsterExtraBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<MonsterExtra> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<MonsterExtra>(end);
    return o;
  }
};

inline flatbuffers::Offset<MonsterExtra> CreateMonsterExtra(
    flatbuffers::FlatBufferBuilder &_fbb,
    double d0 = std::numeric_limits<double>::quiet_NaN(),
    double d1 = std::numeric_limits<double>::quiet_NaN(),
    double d2 = std::numeric_limits<double>::infinity(),
    double d3 = -std::numeric_limits<double>::infinity(),
    float f0 = std::numeric_limits<float>::quiet_NaN(),
    float f1 = std::numeric_limits<float>::quiet_NaN(),
    float f2 = std::numeric_limits<float>::infinity(),
    float f3 = -std::numeric_limits<float>::infinity(),
    flatbuffers::Offset<flatbuffers::Vector<double>> dvec = 0,
    flatbuffers::Offset<flatbuffers::Vector<float>> fvec = 0) {
  MonsterExtraBuilder builder_(_fbb);
  builder_.add_d3(d3);
  builder_.add_d2(d2);
  builder_.add_d1(d1);
  builder_.add_d0(d0);
  builder_.add_fvec(fvec);
  builder_.add_dvec(dvec);
  builder_.add_f3(f3);
  builder_.add_f2(f2);
  builder_.add_f1(f1);
  builder_.add_f0(f0);
  return builder_.Finish();
}

inline flatbuffers::Offset<MonsterExtra> CreateMonsterExtraDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    double d0 = std::numeric_limits<double>::quiet_NaN(),
    double d1 = std::numeric_limits<double>::quiet_NaN(),
    double d2 = std::numeric_limits<double>::infinity(),
    double d3 = -std::numeric_limits<double>::infinity(),
    float f0 = std::numeric_limits<float>::quiet_NaN(),
    float f1 = std::numeric_limits<float>::quiet_NaN(),
    float f2 = std::numeric_limits<float>::infinity(),
    float f3 = -std::numeric_limits<float>::infinity(),
    const std::vector<double> *dvec = nullptr,
    const std::vector<float> *fvec = nullptr) {
  auto dvec__ = dvec ? _fbb.CreateVector<double>(*dvec) : 0;
  auto fvec__ = fvec ? _fbb.CreateVector<float>(*fvec) : 0;
  return MyGame::CreateMonsterExtra(
      _fbb,
      d0,
      d1,
      d2,
      d3,
      f0,
      f1,
      f2,
      f3,
      dvec__,
      fvec__);
}

flatbuffers::Offset<MonsterExtra> CreateMonsterExtra(flatbuffers::FlatBufferBuilder &_fbb, const MonsterExtraT *_o, const flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline MonsterExtraT *MonsterExtra::UnPack(const flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<MonsterExtraT>(new MonsterExtraT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void MonsterExtra::UnPackTo(MonsterExtraT *_o, const flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = d0(); _o->d0 = _e; }
  { auto _e = d1(); _o->d1 = _e; }
  { auto _e = d2(); _o->d2 = _e; }
  { auto _e = d3(); _o->d3 = _e; }
  { auto _e = f0(); _o->f0 = _e; }
  { auto _e = f1(); _o->f1 = _e; }
  { auto _e = f2(); _o->f2 = _e; }
  { auto _e = f3(); _o->f3 = _e; }
  { auto _e = dvec(); if (_e) { _o->dvec.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->dvec[_i] = _e->Get(_i); } } }
  { auto _e = fvec(); if (_e) { _o->fvec.resize(_e->size()); for (flatbuffers::uoffset_t _i = 0; _i < _e->size(); _i++) { _o->fvec[_i] = _e->Get(_i); } } }
}

inline flatbuffers::Offset<MonsterExtra> MonsterExtra::Pack(flatbuffers::FlatBufferBuilder &_fbb, const MonsterExtraT* _o, const flatbuffers::rehasher_function_t *_rehasher) {
  return CreateMonsterExtra(_fbb, _o, _rehasher);
}

inline flatbuffers::Offset<MonsterExtra> CreateMonsterExtra(flatbuffers::FlatBufferBuilder &_fbb, const MonsterExtraT *_o, const flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { flatbuffers::FlatBufferBuilder *__fbb; const MonsterExtraT* __o; const flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _d0 = _o->d0;
  auto _d1 = _o->d1;
  auto _d2 = _o->d2;
  auto _d3 = _o->d3;
  auto _f0 = _o->f0;
  auto _f1 = _o->f1;
  auto _f2 = _o->f2;
  auto _f3 = _o->f3;
  auto _dvec = _o->dvec.size() ? _fbb.CreateVector(_o->dvec) : 0;
  auto _fvec = _o->fvec.size() ? _fbb.CreateVector(_o->fvec) : 0;
  return MyGame::CreateMonsterExtra(
      _fbb,
      _d0,
      _d1,
      _d2,
      _d3,
      _f0,
      _f1,
      _f2,
      _f3,
      _dvec,
      _fvec);
}

inline const flatbuffers::TypeTable *MonsterExtraTypeTable() {
  static const flatbuffers::TypeCode type_codes[] = {
    { flatbuffers::ET_DOUBLE, 0, -1 },
    { flatbuffers::ET_DOUBLE, 0, -1 },
    { flatbuffers::ET_DOUBLE, 0, -1 },
    { flatbuffers::ET_DOUBLE, 0, -1 },
    { flatbuffers::ET_FLOAT, 0, -1 },
    { flatbuffers::ET_FLOAT, 0, -1 },
    { flatbuffers::ET_FLOAT, 0, -1 },
    { flatbuffers::ET_FLOAT, 0, -1 },
    { flatbuffers::ET_DOUBLE, 1, -1 },
    { flatbuffers::ET_FLOAT, 1, -1 },
    { flatbuffers::ET_INT, 0, -1 }
  };
  static const char * const names[] = {
    "d0",
    "d1",
    "d2",
    "d3",
    "f0",
    "f1",
    "f2",
    "f3",
    "dvec",
    "fvec",
    "deprec"
  };
  static const flatbuffers::TypeTable tt = {
    flatbuffers::ST_TABLE, 11, type_codes, nullptr, nullptr, nullptr, names
  };
  return &tt;
}

inline const MyGame::MonsterExtra *GetMonsterExtra(const void *buf) {
  return flatbuffers::GetRoot<MyGame::MonsterExtra>(buf);
}

inline const MyGame::MonsterExtra *GetSizePrefixedMonsterExtra(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<MyGame::MonsterExtra>(buf);
}

inline MonsterExtra *GetMutableMonsterExtra(void *buf) {
  return flatbuffers::GetMutableRoot<MonsterExtra>(buf);
}

inline const char *MonsterExtraIdentifier() {
  return "MONE";
}

inline bool MonsterExtraBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, MonsterExtraIdentifier());
}

inline bool VerifyMonsterExtraBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<MyGame::MonsterExtra>(MonsterExtraIdentifier());
}

inline bool VerifySizePrefixedMonsterExtraBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<MyGame::MonsterExtra>(MonsterExtraIdentifier());
}

inline const char *MonsterExtraExtension() {
  return "mon";
}

inline void FinishMonsterExtraBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<MyGame::MonsterExtra> root) {
  fbb.Finish(root, MonsterExtraIdentifier());
}

inline void FinishSizePrefixedMonsterExtraBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<MyGame::MonsterExtra> root) {
  fbb.FinishSizePrefixed(root, MonsterExtraIdentifier());
}

inline flatbuffers::unique_ptr<MyGame::MonsterExtraT> UnPackMonsterExtra(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return flatbuffers::unique_ptr<MyGame::MonsterExtraT>(GetMonsterExtra(buf)->UnPack(res));
}

inline flatbuffers::unique_ptr<MyGame::MonsterExtraT> UnPackSizePrefixedMonsterExtra(
    const void *buf,
    const flatbuffers::resolver_function_t *res = nullptr) {
  return flatbuffers::unique_ptr<MyGame::MonsterExtraT>(GetSizePrefixedMonsterExtra(buf)->UnPack(res));
}

}  // namespace MyGame

#endif  // FLATBUFFERS_GENERATED_MONSTEREXTRA_MYGAME_H_
