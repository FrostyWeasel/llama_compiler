; ModuleID = 'test.c'
source_filename = "test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.non_locals = type { i32, i32* }

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca %struct.non_locals, align 8
  store i32 5, i32* %1, align 4
  %3 = getelementptr inbounds %struct.non_locals, %struct.non_locals* %2, i32 0, i32 0
  store i32 1, i32* %3, align 8
  %4 = getelementptr inbounds %struct.non_locals, %struct.non_locals* %2, i32 0, i32 1
  store i32* %1, i32** %4, align 8
  %5 = bitcast %struct.non_locals* %2 to i32*
  %6 = call i32 @f(i32 5, i32* %5)
  ret i32 0
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @f(i32 %0, i32* %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32*, align 8
  %5 = alloca %struct.non_locals*, align 8
  store i32 %0, i32* %3, align 4
  store i32* %1, i32** %4, align 8
  %6 = load i32*, i32** %4, align 8
  %7 = bitcast i32* %6 to %struct.non_locals*
  store %struct.non_locals* %7, %struct.non_locals** %5, align 8
  %8 = load i32, i32* %3, align 4
  %9 = load %struct.non_locals*, %struct.non_locals** %5, align 8
  %10 = getelementptr inbounds %struct.non_locals, %struct.non_locals* %9, i32 0, i32 1
  %11 = load i32*, i32** %10, align 8
  %12 = load i32, i32* %11, align 4
  %13 = add nsw i32 %8, %12
  ret i32 %13
}

attributes #0 = { noinline nounwind optnone uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"Ubuntu clang version 12.0.0-3ubuntu1~21.04.1"}
