#include "Displayable.h"

namespace sdds{

    std::ostream& operator<<(std::ostream& os, const Displayable& D) {
        return D.display(os);
    }
}