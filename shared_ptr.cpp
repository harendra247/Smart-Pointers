class RC
{
    private:
    int count = 0; // Reference count

    public:
    void AddRef()
    {
        // Increment the reference count
        count++;
    }

    int DelRef()
    {
        // Decrement the reference count and
        // return the reference count.
        return --count;
    }
};

template<class T>
class SharedPtr
{
private:
	T * ptr = nullptr;
	RC * reference = nullptr;

public:
	SharedPtr() : ptr(nullptr), reference(nullptr) // default constructor
	{
        	// Create a new reference 
		reference = new RC();
		// Increment the reference count
		reference->AddRef();
	}

	SharedPtr(T * ptr) : ptr(ptr), reference(nullptr) // constructor
	{
		// Create a new reference 
		reference = new RC();
		// Increment the reference count
		reference->AddRef();
	}

	/*** Copy Semantics ***/
	SharedPtr(const SharedPtr & obj) // copy constructor
	{
		this->ptr = obj.ptr; // share the underlying pointer
		this->reference = obj.reference;
		if (nullptr != obj.ptr)
		{
			// Increment the reference count
        		reference->AddRef(); // if the pointer is not null, increment the reference count
		}
	}

	SharedPtr& operator=(const SharedPtr & obj) // copy assignment
	{
		Release(); // cleanup any existing data
		
		// Assign incoming object's data to this object
		this->ptr = obj.ptr; // share the underlying pointer
		this->reference = obj.reference;
		if (nullptr != obj.ptr)
		{
			// Increment the reference count
        		reference->AddRef(); // if the pointer is not null, increment the reference count
		}
	}

	/*** Move Semantics ***/
	SharedPtr(SharedPtr && dyingObj) // move constructor
	{
		this->ptr = dyingObj.ptr; // share the underlying pointer
		this->reference = dyingObj.reference;

		dyingObj.ptr = dyingObj.reference = nullptr; // clean the dying object
	}

	SharedPtr& operator=(SharedPtr && dyingObj) // move assignment
	{
		Release(); // cleanup any existing data
		
		this->ptr = dyingObj.ptr; // share the underlying pointer
		this->reference = dyingObj.reference;

		dyingObj.ptr = dyingObj.reference = nullptr; // clean the dying object
	}

	T* get() const
	{
		return this->ptr;
	}

	T* operator->() const
	{
		return this->ptr;
	}

	T& operator*() const
	{
		return *(this->ptr);
	}

	~SharedPtr() // destructor
	{
		Release();
	}

private:
	void Release()
	{
		
		if (reference->DelRef() == 0)
		{
			if (nullptr != ptr)
				delete ptr;
			delete reference;
		}
	}
};
