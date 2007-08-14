#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T> 
class Singleton
{
private:
    Singleton(const Singleton& source) {};
	Singleton &operator=(Singleton const&) {};

protected:
    Singleton() {};
    virtual ~Singleton() {};

public:
    static T& Instance()
    {
		static T m_instance;
		return m_instance;
    };
};

#endif // SINGLETON_H