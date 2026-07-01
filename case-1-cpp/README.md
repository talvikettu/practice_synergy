# Case 1: C++ Birth Date Style Transformer

## Build

Use any C++17-compatible compiler:

```powershell
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o birth_date_app
```

## Run

```powershell
.\birth_date_app.exe
```

The program:

- requests day, month, and year of birth;
- calculates the weekday for the entered date;
- detects whether the year was leap;
- calculates the user's current age;
- prints the birth date as star-styled digits similar to an electronic display.
