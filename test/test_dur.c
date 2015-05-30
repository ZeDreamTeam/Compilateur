int test(int omg, int omg2) {
  int tomg = omg +omg2;
  test(tomg, 1);
}

int main() {
  int a=0;
  int b=2;
  test(a,b);
}

