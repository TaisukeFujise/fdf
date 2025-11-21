# fdf　(fil de fer: wireframe model)

`.fdf` マップを読み込み、行列変換と投影を通してワイヤーフレーム地形を描画するプログラム。

## ディレクトリ概要
- `srcs/app` コンテキスト生成・解放、エントリーポイント、入力バリデーションと終了処理。
- `srcs/io` `.fdf` マップのパース周り。
- `srcs/math` 行列生成と投影変換。
- `srcs/graphics` 描画・イベント処理・HUD・Z バッファ。
- `includes` ヘッダ群。`fdf.h` に構造体・関数・マクロを集約。
- `libft` 42 互換のユーティリティライブラリ。
- `minilibx-linux` ベンダ提供の描画ライブラリ。
- `test_maps` 付属の動作確認用マップ。

## ビルドと実行
```sh
make            # バイナリ fdf を生成
./fdf <map.fdf> # 例: ./fdf test_maps/42.fdf
```

