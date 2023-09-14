#include "Rect.h"
#include "Pin.h"
#include "Cell.h"

int main() {
    Rect rect{1.2, 1.4, 7.3, 3.4};
    Pin pin("A", rect);
    Cell cell("$and", {pin});
    return 0;
}
