#include "VirtualWardrobeApp.h"

int main() {
    VirtualWardrobeApp app("wardrobe_data.txt", "user_profile.txt");
    app.run();
    return 0;
}
