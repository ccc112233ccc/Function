#include <memory>

namespace ccutil {
template <typename Ret, typename... Args>
struct Function;

template <typename Ret, typename... Args>
struct Function<Ret(Args...)> {
  Ret operator()(Args... args) { return m_holder->call(args...); }

  template <typename Func>
  Function(Func func) : m_holder(new Holder<Func>(func)) {}

  Function() = default;
  Function(const Function& other) {
    if (other.m_holder) {
      m_holder.reset(other.m_holder->clone());
    }
  }
  Function& operator=(const Function& other) {
    if (other.m_holder) {
      m_holder.reset(other.m_holder->clone());
    }
    return *this;
  }

  Function(Function&&) = default;
  Function& operator=(Function&&) = default;

  ~Function() = default;

  template <typename Func>
  Function& operator=(Func func) {
    m_holder.reset(new Holder<Func>(func));
    return *this;
  }
  explicit operator bool() const { return static_cast<bool>(m_holder); }
  void reset() { m_holder.reset(); }

 private:
  struct BaseHolder {
    virtual ~BaseHolder() = default;
    virtual Ret call(Args...) = 0;
    virtual BaseHolder* clone() = 0;
  };

  template <typename Func>
  struct Holder : BaseHolder {
    Holder(Func func) : m_func(func) {}

    Ret call(Args... args) override { return m_func(args...); }
    BaseHolder* clone() override { return new Holder(m_func); }

    Func m_func;
  };

  std::unique_ptr<BaseHolder> m_holder;
};
}  // namespace ccutil