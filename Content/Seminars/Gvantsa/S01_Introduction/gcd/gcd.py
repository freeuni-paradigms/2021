def calc_gcd(x, y):
   while(y):
       x, y = y, x % y
   return x

print("Enter two integers:")
x, y = map(int, input().split())
gcd = calc_gcd(x, y)
print("The GCD of", x, " and ", y, " is", gcd)
