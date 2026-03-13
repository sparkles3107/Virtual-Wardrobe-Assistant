# Virtual Wardrobe Assistant ? Viva Script (1 Page)

Good morning. My project is **Virtual Wardrobe Assistant**, developed in **C++ using OOP** with a **Qt Widgets GUI**. The goal is to store a user?s wardrobe and profile, then recommend outfit combinations based on personal attributes and occasion.

## What the system does
- Stores a **user profile**: age, skin tone, height category, preferred style.
- Stores **wardrobe items**: type, color, style, occasion, pattern, length.
- Recommends the best **top + bottom** outfit using a scoring engine.
- Uses **file handling** so data is saved and loaded automatically each time.

## OOP design used
- **ClothingItem**: represents each clothing piece and supports serialization to file.
- **UserProfile**: represents the user?s personal preferences.
- **FileManager**: handles reading/writing `user_profile.txt` and `wardrobe_data.txt`.
- **WardrobeManager**: adds/removes items and manages IDs.
- **RecommendationEngine**: applies decision logic and scoring.
- **MainWindow (Qt GUI)**: connects UI actions to backend logic.

## Recommendation logic
For every top?bottom pair, the engine adds points for:
- **Style match** (formal/casual/trendy, etc.)
- **Occasion match** (party/casual/office)
- **Skin tone suitability** (warm vs cool color groups)
- **Height-based rules** (vertical stripes for short, long outerwear for tall)
- **Age-style compatibility** (e.g., trendy for younger, classic/formal for older)

The pair with the highest score becomes the recommendation.

## GUI overview (Qt)
- **Profile tab**: input age, skin tone, height, preferred style.
- **Wardrobe tab**: add item, view table, remove by ID.
- **Recommendation tab**: select occasion/style and get best outfit.

## Files used
- `user_profile.txt` ? stores profile as one line.
- `wardrobe_data.txt` ? stores each clothing item as one line.

## OOP concepts demonstrated
- **Encapsulation**: private data + public getters/setters.
- **Abstraction**: recommendation logic hidden behind a single `recommend()` method.
- **Composition**: MainWindow contains managers and engine objects.
- **Inheritance**: MainWindow extends `QMainWindow`.
- **Constructor overloading**: default and parameterized constructors.

## Conclusion
This project shows practical use of OOP and file handling in C++ while delivering a real-world GUI application. It is modular, maintainable, and easy to extend.
