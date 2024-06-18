define dso_local signext i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %x = alloca i32, align 4
  store i32 0, ptr %retval, align 4
  store i32 10, ptr %x, align 4
  %0 = load i32, ptr %x, align 4
  %nouman = add nsw i32 %0, 2
  store i32 %nouman, ptr %x, align 4
  ret i32 0
}