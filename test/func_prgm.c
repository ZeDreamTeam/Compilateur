int add(int init, int souhait) {
  int a = init;

  if(a < init) {
    add(a+1, souhait);
  }
}

int main() {
  int a=0;
  int b=2;
  add(a,b);
}

