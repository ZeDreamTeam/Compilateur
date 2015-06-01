int test(int omg, int omg2) {
  int tomg = omg +omg2;
  int i;
  while(i>omg) {
    tomg=tomg-i;
  }
  test(tomg, 1);
}

int main() {
  int a=0;
  int b=2;
  if(a>b) {
    test(b,a);
  } else {
    test(a,b);
  }
}

