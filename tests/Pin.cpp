#include "Rect.h"
#include "Pin.h"

int main() {
    Rect rect{1.2, 1.4, 7.3, 3.4};
    Pin pin("A", rect);
    return 0;
}
