# T-motor_controller_F767ZI
・FreeRTOS  
・SDMMC  
・CAN通信  
以上3点を組み合わせ，T-motorを制御しつつSDカードにロギングが出来ることを目指したプロジェクト．  
  
# motor_statusクラス
モータの状態，目標値をまとめたクラス．  

# T_motor_controllerクラス
コントローラクラス．  
メンバ変数に上記のmotor_statusクラスを持つ．
メンバ関数を呼び出すことでモータ制御が行えるようにしている．


# 現状の問題点
SDMMCとFatFSの相性が悪く，f_open()関数を呼び出すとエラーが発生．
（返り値がFR_NOT_READYとなってしまう）