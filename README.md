# cxademangle

Clang / GNU C++ 等でコンパイルしたシンボル名を表記名に変換する Python モジュールです。

## インストール

実行ユーザー向けにモジュールをインストールします。

```
% make install
```

## 使用方法

メソッドは１つだけです。

```
demangle(name: str) -> str:
```

**使用例**

```
>>> import cxademangle
>>> cxademangle.demangle('__ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEElsEi')
'std::__1::basic_ostream<char, std::__1::char_traits<char>>::operator<<(int)'
```

## 実装

変換では以下の関数を使用します。

```
#include <cxxabi.h>
char *abi::__cxa_demangle( /*略*/ );
```
