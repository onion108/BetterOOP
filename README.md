# Usage
Just download the two headers and add them into your project.
For example, you can
```C++
BetterOOP::Nullable<int> i = BetterOOP::nil;
```
or add some declartion like this
```C++
BetterOOP::Property<int> aReadonlyProp([](T& _unused) { return 3 });
std::cout << aReadonlyProp;
```
