# cppcheckでMISRA 2012をチェックする方法
cppcheckでは不完全ではありますが、[misra-c 2012のチェック](http://cppcheck.sourceforge.net/misra.php)が可能です。
vscode等に組み込むことで手元で静的解析が可能です。

このプロジェクトを使用すると、VSCodeでMISRA-C 2012のチェックをかけることができます。


# environment
OS:Windows 10
others:VSCode, python

# setup
## python
https://www.python.jp/ からインストーラをダウンロードしてインストールします。
”Add to PATH”にチェック入れるのを忘れずに。


## vscode
 * VSCodeのワークスペースの.vscodeフォルダにmisra_check/tasks.jsonをコピー。他のプロジェクトにgit subomodule addした場合はcommandのパスを適宜書き換えてください。
 ```
    "version": "2.0.0",
	"tasks": [
		{
            "label": "misra",
            "type": "shell",
            "command": "${workspaceFolder}\\static-analyze\\misra_chk.bat ${workspaceFolder}\\static-analyze ${file}",
            "problemMatcher": []
		}
	]
 ```
 
 * VSCodeのkeybindings.jsonに以下を追加。もしくはキーボードショートカットから”workbench.action.tasks.runTask”で検索して追加
 ```
    {
        "key": "shift+alt+m",
        "command": "workbench.action.tasks.runTask",
        "args": "misra",
    }
 ```

# 実行
VSCで*.cを開いた状態でAlt+Shift+mを押すと解析が実行されます。
```
> Executing task in folder MISRA-C_Check: D:\Workspace\MISRA-C_Check\static-analyze\misra_chk.bat D:\Workspace\MISRA-C_Check\static-analyze d:\Workspace\MISRA-C_Check\target\sample.c <


d:\Workspace\MISRA-C_Check>D:\Workspace\MISRA-C_Check\static-analyze\CppCheck\cppcheck.exe --dump d:\Workspace\MISRA-C_Check\target\sample.c
Checking d:\Workspace\MISRA-C_Check\target\sample.c ...
Checking d:\Workspace\MISRA-C_Check\target\sample.c: WIN_TEST...

d:\Workspace\MISRA-C_Check>python D:\Workspace\MISRA-C_Check\static-analyze\CppCheck\addons\misra.py --rule-texts=D:\Workspace\MISRA-C_Check\static-analyze\misra2012-rule.txt d:\Workspace\MISRA-C_Check\target\sample.c.dump
Checking d:\Workspace\MISRA-C_Check\target\sample.c.dump...
Checking d:\Workspace\MISRA-C_Check\target\sample.c.dump, config ""...
[d:/Workspace/MISRA-C_Check/target/sample.c:99] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-4.1] 
[d:/Workspace/MISRA-C_Check/target/sample.c:107] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-4.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:117] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-4.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:180] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-4.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:312] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-4.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:327] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-4.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:331] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-4.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:384] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-4.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:207] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-5.3]
[d:/Workspace/MISRA-C_Check/target/sample.c:228] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-5.3]
[d:/Workspace/MISRA-C_Check/target/sample.c:210] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-10.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:210] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-10.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:230] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-10.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:230] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-10.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:273] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-10.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:287] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-10.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:294] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-10.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:306] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-10.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:318] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-10.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:363] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-10.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:88] (style) JP:ここにMISRA-C 2012の文を載せてください (Advisory) [misra-c2012-11.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:179] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-11.8]
[d:/Workspace/MISRA-C_Check/target/sample.c:273] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-14.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:287] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-14.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:294] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-14.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:175] (style) JP:ここにMISRA-C 2012の文を載せてください (Advisory) [misra-c2012-15.5]
[d:/Workspace/MISRA-C_Check/target/sample.c:61] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:64] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:66] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:158] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:213] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:233] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:274] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:276] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:281] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:283] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:288] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:290] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:295] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:297] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:342] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:348] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:177] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.7]
[d:/Workspace/MISRA-C_Check/target/sample.c:43] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-21.6]
Checking d:\Workspace\MISRA-C_Check\target\sample.c.dump, config "WIN_TEST"...
[d:/Workspace/MISRA-C_Check/target/sample.c:207] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-5.3]
[d:/Workspace/MISRA-C_Check/target/sample.c:228] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-5.3]
[d:/Workspace/MISRA-C_Check/target/sample.c:210] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-10.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:210] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-10.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:230] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-10.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:230] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-10.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:273] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-10.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:287] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-10.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:294] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-10.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:306] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-10.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:318] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-10.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:363] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-10.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:179] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-11.8]
[d:/Workspace/MISRA-C_Check/target/sample.c:273] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-14.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:287] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-14.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:294] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-14.4]
[d:/Workspace/MISRA-C_Check/target/sample.c:175] (style) JP:ここにMISRA-C 2012の文を載せてください (Advisory) [misra-c2012-15.5]
[d:/Workspace/MISRA-C_Check/target/sample.c:61] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:64] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:66] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:158] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:213] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:233] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:274] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:276] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:281] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:283] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:288] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:290] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:295] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:297] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:342] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:348] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.1]
[d:/Workspace/MISRA-C_Check/target/sample.c:71] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.7]
[d:/Workspace/MISRA-C_Check/target/sample.c:177] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-17.7]
[d:/Workspace/MISRA-C_Check/target/sample.c:43] (style) JP:ここにMISRA-C 2012の文を載せてください (Required) [misra-c2012-21.6]

MISRA rules violations found:
        Required: 77
        Advisory: 3

MISRA rules violated:
        misra-c2012-4.1 (-): 8
        misra-c2012-5.3 (-): 4
        misra-c2012-10.4 (-): 20
        misra-c2012-11.4 (-): 1
        misra-c2012-11.8 (-): 2
        misra-c2012-14.4 (-): 6
        misra-c2012-15.5 (-): 2
        misra-c2012-17.1 (-): 32
        misra-c2012-17.7 (-): 3
        misra-c2012-21.6 (-): 2

d:\Workspace\MISRA-C_Check>del d:\Workspace\MISRA-C_Check\target\sample.c.dump

ターミナルはタスクで再利用されます、閉じるには任意のキーを押してください。

```

# 肝心のルール本文
ルールテキストの配布は[使用許諾](https://sourceforge.net/p/cppcheck/discussion/general/thread/ccbe9e89/)が必要っぽいのでここでは配布しません。

おとなしく[€15はらって公式からPDFを買いましょう](https://www.misra.org.uk/Buyonline/tabid/58/Default.aspx)。

購入したらmisra2012-rule.txtを書き換えてください。

# LICENSE
 * GPL v3

# using Libraries
* cppcheck (https://github.com/danmar/cppcheck)
  > GPL v3 (static-analyze/COPYING)
