#pragma once
#include <functional>
#include <optional>
// clang-format off

template <class T> class opt_ref 
{
  using std_opt_ref = std::optional<std::reference_wrapper<T>>;
  std_opt_ref data = std::nullopt;

public:

  using type = typename std::reference_wrapper<T>::type;

  T &get() { return data.value().get(); }

  const T &get() const { return data.value().get(); }

  bool has_value() const { return data.has_value(); }

  opt_ref() {}

  opt_ref(T &source) : data(source) {}

  opt_ref &operator=(T &&other) 
  {
    data.value().get() = other;
    return *this;
  }
};