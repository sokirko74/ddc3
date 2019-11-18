#ifndef ptrholder_h
#define ptrholder_h


template <class T>
class PtrHolder {
public:
    inline PtrHolder(T* t = 0) throw ()
        : T_(t)
    {
    }

    inline PtrHolder(PtrHolder& that)
        : T_(that.Release())
    {
    }

    inline ~PtrHolder() throw () {
        DoDestroy();
    }

    inline void Destroy() throw () {
        Reset(0);
    }

    inline T* operator-> () const throw () {
        return AsT();
    }

    template <class C>
    inline bool operator== (const C& p) const {
        return (p == AsT());
    }

    template <class C>
    inline bool operator!= (const C& p) const {
        return (p != AsT());
    }

    inline operator bool () const {
        return 0 != AsT();
    }

    inline T* Release() {
        T* ret = T_;
        T_ = 0;
        return ret;
    }

    inline void Reset(T* t) {
        if (T_ != t) {
            DoDestroy();
            T_ = t;
        }
    }

    inline T* Get() const {
        return T_;
    }

    PtrHolder& operator= (PtrHolder& that) {
        this->Reset(that.Release());
        return *this;
    }

    T& operator* () const {
        assert(this->AsT());

        return *(this->AsT());
    }

private:
    void DoDestroy() {
        if (T_) {
            delete T_;
        }
    }
    T* AsT() const {
        return (static_cast<PtrHolder<T>*>(this))->Get();
    }


private:
    T* T_;
};

#endif

/*--- emacs style variables ---
 * Local Variables:
 *  mode: C++
 *  c-file-style: "ellemtel"
 *  c-basic-offset: 4
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
