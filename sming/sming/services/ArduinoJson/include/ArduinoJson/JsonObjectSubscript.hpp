// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

#include "JsonSubscriptBase.hpp"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4522)
#endif

namespace ArduinoJson {

template <typename TKey>
class JsonObjectSubscript
    : public JsonSubscriptBase<JsonObjectSubscript<TKey> > {
 public:
  FORCE_INLINE JsonObjectSubscript(JsonObject& object, TKey key)
      : _object(object), _key(key) {}

  using JsonSubscriptBase<JsonObjectSubscript<TKey> >::operator=;

  JsonObjectSubscript<TKey>& operator=(const JsonObjectSubscript<TKey>& src) {
    return JsonSubscriptBase<JsonObjectSubscript<TKey> >::template assign<
        JsonVariant>(src);
  }

  template <typename T>
  JsonObjectSubscript<TKey>& operator=(const T& src) {
    return JsonSubscriptBase<JsonObjectSubscript<TKey> >::template assign<
        JsonVariant>(src);
  }

  FORCE_INLINE bool success() const { return _object.containsKey(_key); }

  FORCE_INLINE operator JsonVariant() const { return _object.get(_key); }

  template <typename TValue>
  FORCE_INLINE TValue as() const {
    return _object.get<TValue>(_key);
  }

  template <typename TValue>
  FORCE_INLINE bool is() const {
    return _object.is<TValue>(_key);
  }

  template <typename TValue>
  FORCE_INLINE bool set(TValue value) {
    return _object.set(_key, value);
  }

  FORCE_INLINE JsonVariant get() { return _object.get(_key); }

  void writeTo(Internals::JsonWriter& writer) const {
    _object.get(_key).writeTo(writer);
  }

 private:
  JsonObject& _object;
  TKey _key;
};

#ifdef ARDUINOJSON_ENABLE_STD_STREAM
inline std::ostream& operator<<(
    std::ostream& os, const JsonObjectSubscript<const String&>& source) {
  return source.printTo(os);
}

inline std::ostream& operator<<(
    std::ostream& os, const JsonObjectSubscript<const char*>& source) {
  return source.printTo(os);
}
#endif
}  // namespace ArduinoJson

#ifdef _MSC_VER
#pragma warning(pop)
#endif
