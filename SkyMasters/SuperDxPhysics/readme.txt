SuperDxPhysics の使い方

※注意　全然未完成なのであくまで"仮"です。

----------------------------------------------------------------

◇導入方法

① Cドライブ直下にDxLibを置く
② DxLibを通常通り導入する
③ プロジェクト->プロパティを開く
④ 「C/C++」の「全般」->「追加のインクルードディレクトリ」にこのreadmeと同じ階層にある「AddFiles」フォルダのパスを設定
⑤ 「リンカー」の「全般」->「追加のライブラリディレクトリ」にも同じ「AddFiles」フォルダのパスを設定
⑥ 「リンカー」の「入力」->「追加の依存ファイル」にDebugなら「libScePhysicsEffectsD.lib」、Releaseなら「libScePhysicsEffects.lib」を入力
⑦ ソリューションエクスプローラーに「AddFiles」内の.hと.cppを追加する
　 (ライブラリのような使いやすい形にまだなっていないため。間違って改変しないよう新しいフィルターを追加し、その中に追加するとよい。)
⑧ 使用したいスクリプトで「SuperDxPhysics.h」をインクルードする
　 コピー用-> #include "SuperDxPhysics.h"

----------------------------------------------------------------

◇使い方

・GamePhysicsSdkの関数等は「sce::PhysicsEffects」、SuperDxPhysicsの関数は「SDxPh」という名前空間上にあります
　「using namespace sce::PhysicsEffects;」や「using namespace SDxPh;」とすると使いやすいです

・関数の宣言は「SuperDxPhysics.h」に、定義は「SuperDxPhysics.cpp」にあります

・関数の引数や返り値は基本的に通常の変数やDxLibの変数ですが
　「CreatePhysicalSphere」を始めとする物理オブジェクトの生成関数ではGamePhysicsSdkの「ePfxMotionType」という型の変数を用います
　オブジェクトのふるまいを決めるもので、以下のように定数で宣言されています

　kPfxMotionTypeFixed
　kPfxMotionTypeActive
　kPfxMotionTypeKeyframe
　kPfxMotionTypeOneWay
　kPfxMotionTypeTrigger
　(kPfxMotionTypeCount)