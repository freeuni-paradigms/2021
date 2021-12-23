---
nav_order: 4
title: C - Array2D
parent: ფინალური გამოცდის საკითხების მაგალითები
grand_parent: სავარჯიშოები
---

# Array2D - ჯენერიკები

ამოცანა დაყოფილია ორ ნაწილად. პირველ ნაწილში უნდა გაუკეთოთ ორგანზომილებიან მასივს Array2D იმპლემენტაცია. ხოლო მეორე ნაწილში მისი გამოყენებით იმპლემენტაცია უნდა გაუკეთოთ სტრიქონებისთვის სპეციალიზირებულ ორგანზომილებიან მასივს StrArray2D.

## Array2D - 70%
Array2D სტრუქტურას უნდა ქონდეს შემდეგი ინტერფეისი:

* void Array2DInit(Array2D* arr, int n, int m, int elem_size, FreeFn free_fn) - უნდა შეასრულოს გადაცემული მასივის ინიციალიზაცია. n აღნიშნავს ხაზების რაოდენობას, m სვეტების რაოდენობას, elem_size თუ რა ზომისაა ბაიტებში მასივის თითოეული ელემენტი, free_fn ფუნქციზე მიმთითებელი რომელიც **თუ საჭიროა** უნდა გამოიძახებოდეს მასივის ელემენტების მიერ გამოყენებული მეხსიერების გასანთავისუფლებლად.
* void Array2DDestroy(Array2D* arr) - უნდა გაანთავისუფლოს მასივის მიერ გამოყენებული მეხსიერება.
* int Array2DN(Array2D* arr) - უნდა დააბრუნოს მასივში ხაზების რაოდენობა.
* int Array2DM(Array2D* arr) - უნდა დააბრუნოს მასივში სვეტების რაოდენობა.
* void Array2DSet(Array2D* arr, int i, int j, void* value) - მასივის (i, j) ელემენტში უნდა ჩაწეროს ელემენტის რომლის მნიშვნელობაც value მისამართდან იწყება. **მასივი გადაცემულ ელემენტის მნიშვნელობაზე იღებს მფლობელობას**.
* const void* Array2DGet(Array2D* arr, int i, int j) - უნდა დააბრუნოს მასივში (i, j) პოზიციაზე მყოფი ელემენტის მისამართი.
* void Array2DRemove(Array2D* arr, int i, int j) - მასივიდან უნდა "გაანულოს" (i, j) პოზიციაზე მყოფი ელემენტი, მხოლოდ იმ შემთვევაში თუ იგივე პოზიციაზე ელემენტი უკვე იყო ჩაწერილი. განულებაში იგულისხმება რომ მასივმა უნდა დაიმახსოვროს რომ მოცემულ პოზიციაზე არაფერი აღარ წერია.
* void Array2DIterate(Array2D* arr, int x, int y, int w, int z, IterFn iter_fn, void* aux) - მასივში (x, y) პოზიციიდან (w, z) პოზიციის ჩათვლით ყოველი **ჩაწერილი** ელემენტისთვის უნდა გამოიძახოს გადაცემული iter_fn ფუნქცია. ყოველ გამოძახებაზე iter_fn ფუნქციას არგუმენტებად უნდა გადაეცეს: aux გადმოცემული დამატებითი ინფორმაცია, მასივის მიმდინარე ელემენტზე მიმთითებელი, და მისი კოორდინატები. ** ყურადღება მიაქციეთ სიტყვა ჩაწერილს წინა წინადადებაში.**
* void Array2DGrow(Array2D* arr, int n, int m) - უნდა გაზარდოს მასივი. გადმოცემული მასივის ახალი ზომები ყოველთვის მეტი ან ტოლი იქნება ძველ ზომაზე, ანუ n >= arr->n && m >= arr->m

## StrArray2D - 30%
**StrArray2D სტრუქტურის იმპლემენტაციისას გამოიყენეთ მხოლოდ Array2D-ის ინტერფეისი და არა მისი შიდა მონაცემები (სტრუქტურის ცვლადები), წინააღმდეგ შემთხვევაში ამოცანის ამ ნაწილში ქულა არ დაგეწერებათ.**

StrArray2D სტრუქტურას უნდა ქონდეს შემდეგი ინტერფეისი:

* void StrArray2DInit(StrArray2D* arr, int n, int m) - უნდა შეასრულოს გადაცემული სტრიქონების მასივის ინიციალიზაცია.
* void StrArray2DDestroy(StrArray2D* arr) - უნდა გაანთავისუფლოს სტრიქონების მასივის მიერ გამოყენებული მეხსიერება.
* void StrArray2DSet(StrArray2D* arr, int i, int j, char* str) - მასივის (i, j) პოზიციაზე უნდა ჩაწეროს გადაცემული სტრიქონი, **რომელზეც ის იღებს მფლობელობას**.
* const char* StrArray2DGet(StrArray2D* arr, int i, int j) - უნდა დააბრუნოს მასივში (i, j) პოზიციაზე მყოფი სტრიქონი.
* bool StrArray2DRemove(StrArray2D* arr, const char* str) - მასივში უნდა იპოვოს და წაშალოს მოცემული სტრიქონი, ასეთის არსებობის შემთხვევაში. ძებნა უნდა მოხდეს ხაზების ზრდადობის მიხედვით, მარცხნიდან მარჯვნივ. ანუ ჯერ პირველ ხაზზე უნდა შემოწმდეს ყველა ელემენტი მარცხნიდან მარჯვნივ, შემდეგ მეორე ხაზზე და ა.შ. უნდა დააბრუნოს true თუ ასეთი ელემენტი იპოვა და წაიშალა, ხოლო false წინააღმდეგ შემთხვევაში. **ამ ფუნქციის იმპლემენტაციაში მხოლოდ შეგიძლიათ აღწეროთ ცვლადები, გამოიძახოთ მხოლოდ Array2DIterate ფუნქცია და დააბრუნოთ უკან პასუხი. არ გაქვთ უფლება გამოიყენოთ if/else, for/while კოსნტრუქციები.**

## ტესტირება
ფაილების კომპილაციისთვის გაუშვით **gcc *.c** 
ხოლო დაკომპილირებული ფაილების გასაშვებად: **a.exe**

## შეფასება
Array2D: საკითხისთვის განკუთვნილი ქულის 70%
StrArray2D: საკითხისთვის განკუთვნილი ქულის 30%

**თითოეულ ტესტზე ინდივიდუალურად შემოწმდება თქვენი ამოხსნა სწორად იყენებს თუ არა მეხსიერებას. ყოველ წარმატებულად გავლილ ტესტზე რომლის შესრულების დროსაც თქვენი ნამუშევარი მეხსიერებას არასწორად გამოიყენებს დაგაკლდებათ ტესტისთვის განკუთვნილი ქულის 15%. სწორად გამოყენებაში იგულისხმება რომე აპლიკაცია უნდა იყენებდეს მხოლოდ მისთვის გამოყოფილ მეხსიერებას და აპლიკაციის დასრულებამდე ყველა დინამიურად გამოყოფილი მეხსერება უნდა გაათავისუფლოთ.**

## შეიძლება დაგჭირდეთ შემდეგი ფუნქციები სტანდარტული ბიბლიოთეკიდან:

### <stdlib.h>
* void* malloc( size_t size ); -- Allocates size bytes of uninitialized storage.
* void *realloc( void *ptr, size_t new_size ); -- Reallocates the given area of memory. It must be previously allocated by malloc(), calloc() or realloc() and not yet freed with a call to free or realloc. Otherwise, the results are undefined.
* void free( void* ptr ); -- Deallocates the space previously allocated by malloc(), calloc(), aligned_alloc, (since C11) or realloc().

### <string.h>
* void* memcpy( void *dest, const void *src, size_t count ); -- Copies count characters from the object pointed to by src to the object pointed to by dest. Both objects are interpreted as arrays of unsigned char.
* void* memmove( void* dest, const void* src, size_t count ); -- Copies count characters from the object pointed to by src to the object pointed to by dest. Both objects are interpreted as arrays of unsigned char. The objects may overlap: copying takes place as if the characters were copied to a temporary character array and then the characters were copied from the array to dest.
 The behavior is undefined if access occurs beyond the end of the dest array. The behavior is undefined if either dest or src is a null pointer.
* char * strdup(const char *str1); -- Returns a pointer to a null-terminated byte string, which is a duplicate of the string pointed to by str1. The returned pointer must be passed to free to avoid a memory leak.
* char *strndup(const char *str, size_t size); -- Returns a pointer to a null-terminated byte string, which contains copies of at most size bytes from the string pointed to by str. If the null terminator is not encountered in the first size bytes, it is added to the duplicated string.
* int strcmp ( const char * str1, const char * str2 ); - Compares the C string str1 to the C string str2. This function starts comparing the first character of each string. If they are equal to each other, it continues with the following pairs until the characters differ or until a terminating null-character is reached. This function performs a binary comparison of the characters. For a function that takes into account locale-specific rules, see strcoll.
