#pragma once
template <typename T>
class Singleton {
public:
		// Function to access the singleton instance
		static T& getInstance() {
				static T instance; // Guaranteed to be destroyed and instantiated only once.
				return instance;
		}

		// Delete the copy constructor and assignment operator to prevent duplication
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;

protected:
		// Allow derived classes to access the constructor
		Singleton() = default;
};