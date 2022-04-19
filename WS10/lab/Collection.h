#ifndef SDDS_COLLECTION_H_
#define SDDS_COLLECTION_H_

namespace sdds {

    // Collection class is a template that works like a dynamic array of objects with a constant size
    // Supports the rule of three

    //int i;
    //Collection<double> dbls(4);   // initialize dbls as a Collection (array of doubles of size 4)
    // 
    //for (i = 0; i < 4; i++) {
    //    dbls[i] = 1.1 + i;        // set each element of the array to a value starting with 1.1, 2.1, etc
    //}
    // 
    //cout << "There are " << dbls.size() << " items in the Collection:" << endl;   // print number of elements of array which is 4
    // 
    //for (i = 0; i < 4; i++) {
    //    cout << dbls[i] << " ";       // print each element which is 1.1, 2.1, etc
    //}
    // 
    //cout << endl;

    template <class type>
    class Collection {

        type* m_objs{};         // dynamic array of objects - we do not know what type
        unsigned m_size{};      // size of the array
    
    public:
        // constructor
        Collection(unsigned size=0) : m_size( size ) {
            if(size) m_objs = new type[size];
        }

        // copy constructor
        Collection(const Collection<type>& S) {
            operator=(S);
        }

        // overloaded assignment operator
        // sets the reference to the element of the array to value
        Collection<type>& operator=(const Collection<type>& S) {
            delete[] m_objs;
            m_size = 0;
            if (S.m_size && this != &S) {
            m_objs = new type[m_size = S.m_size];
            for (unsigned i = 0; i < m_size; i++)  m_objs[i] = S.m_objs[i];
            }
            return *this;
        }

        // destructor
        virtual ~Collection() {
            delete[] m_objs;
        }

        // query function - returns size of array
        unsigned size() const {
            return m_size;
        }

        // modifier function - returns a reference to the element in the array
        type& operator[](unsigned i) {
            return m_objs[i % m_size];
        }

        // query function - returns a reference to the element in the array (unmodifiable)
        const type& operator[](unsigned i) const {
            return m_objs[i % m_size];
        }
    };
}
#endif // ! SDDS_COLLECTION_H_

