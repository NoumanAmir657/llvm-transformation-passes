; ModuleID = 'examples/foo2.ll'
source_filename = "examples/foo2.ll"

define dso_local signext i32 @main() {
entry:
  %retval = alloca i32, align 4
  %x = alloca i32, align 4
  store i32 0, ptr %retval, align 4
  store i32 10, ptr %x, align 4
  %0 = load i32, ptr %x, align 4
  %add1 = sub i32 %0, 2
  store i32 %add1, ptr %x, align 4
  ret i32 0
}
