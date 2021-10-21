template < typename T > 
class SP {
    private:
        T*    ptr; // Generic pointer to be stored
    public:
        SP(T* pValue) : ptr(pValue) { }
        ~SP()
        {
            delete ptr;
        }

        T& operator* ()
        {
            return *ptr;
        }

        T* operator-> ()
        {
            return ptr;
        }
};

int main() {
    SP<int> p(new int);
    *p = 25;
    return 0;
}
