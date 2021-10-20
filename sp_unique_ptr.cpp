template <class T>
class sp_unique_ptr
{
private:
	T * ptr = nullptr;

public:
	sp_unique_ptr() : ptr(nullptr) // default constructor
	{
	}

	sp_unique_ptr(T * ptr) : ptr(ptr)
	{
	}

	sp_unique_ptr(const sp_unique_ptr & obj) = delete; // copy constructor is deleted
	sp_unique_ptr& operator=(const sp_unique_ptr & obj) = delete; // copy assignment is deleted

	sp_unique_ptr(sp_unique_ptr && dyingObj) // move constructor
	{
		// Transfer ownership of the memory pointed by dyingObj to this object
		this->ptr = dyingObj.ptr;
		dyingObj.ptr = nullptr; 
	}

	void operator=(sp_unique_ptr && dyingObj) // move assignment
	{
		Free(); // cleanup any existing data

		// Transfer ownership of the memory pointed by dyingObj to this object
		this->ptr = dyingObj.ptr;
		dyingObj.ptr = nullptr;
	}

	T* operator->() // deferencing arrow operator
	{
		return this->ptr;
	}

	T& operator*()
	{
		return *(this->ptr);
	}

	~sp_unique_ptr() // destructor
	{
		Free();
	}

private:
	void Free()
	{
		if (ptr != nullptr)
			delete ptr;
	}
};
