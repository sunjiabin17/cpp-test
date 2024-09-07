#pragma once

#include <type_traits>
#include <utility>

namespace iter {

template <typename F>
struct IterArgs {
  template <typename... Args>
  inline F& apply() {
    return self();
  }

  template <typename T, typename... Args>
  inline F& apply(T&& arg, Args&&... args) {
    self()(std::forward<T>(arg));
    return apply(std::forward<Args>(args)...);
  }

private:
  inline F& self() {
    return *static_cast<F*>(this);
  }
};

}
