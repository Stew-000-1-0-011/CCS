# StewDxEngineのメモ
## 方針
- 主要なOSでサポートされている機能のみ入れる
- なんたらHandleクラスは基本非nullで最低限の機能しかもたせない。std::shared_ptrで包んで、それを持つクラスで色々実装する。
nullはnullptrで表す。
  - ex) ```Graph```が```std::shared_ptr<GraphHandle>```を持っていて、```Graph```で```DxLib::LoadGraph```とかを呼び出している
- Sourcetrail使って見てほしい

## Graphまわり
- 透明度に関する機能は一貫性がないので取り込まなかった。
- 