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
> Executing task in folder MISRA-C_Check: D:\WorkSpace\MISRA-C_Check\static-analyze\misra_chk.bat D:\WorkSpace\MISRA-C_Check\static-analyze d:\WorkSpace\MISRA-C_Check\target\sample.c <


d:\WorkSpace\MISRA-C_Check>wsl /mnt/d/WorkSpace/MISRA-C_Check/static-analyze/Cppcheck/cppcheck --dump /mnt/d/WorkSpace/MISRA-C_Check/target/sample.c
Checking /mnt/d/WorkSpace/MISRA-C_Check/target/sample.c ...
Checking /mnt/d/WorkSpace/MISRA-C_Check/target/sample.c: WIN_TEST...

d:\WorkSpace\MISRA-C_Check>python D:\WorkSpace\MISRA-C_Check\static-analyze\Cppcheck\addons\misra.py --rule-texts=D:\WorkSpace\MISRA-C_Check\static-analyze\misra2012-rule.txt d:\WorkSpace\MISRA-C_Check\target\sample.c.dump
Checking d:\WorkSpace\MISRA-C_Check\target\sample.c.dump...
Checking d:\WorkSpace\MISRA-C_Check\target\sample.c.dump, config ""...
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:369]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-5.2]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:378]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-5.2]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:207]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-5.3]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:228]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-5.3]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:210]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-10.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:230]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-10.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:273]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-10.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:287]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-10.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:294]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-10.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:306]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-10.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:318]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-10.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:363]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-10.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:88]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-11.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:273]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-14.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:287]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-14.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:294]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-14.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:175]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-15.5]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:61]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:64]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:66]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:158]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:213]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:233]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:274]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:276]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:281]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:283]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:288]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:290]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:295]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:297]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:342]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:348]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:43]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-21.6]
Checking d:\WorkSpace\MISRA-C_Check\target\sample.c.dump, config "WIN_TEST"...
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:378]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-5.2]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:369]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-5.2]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:207]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-5.3]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:228]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-5.3]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:210]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-10.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:230]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-10.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:273]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-10.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:287]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-10.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:294]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-10.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:306]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-10.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:318]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-10.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:363]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-10.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:273]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-14.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:287]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-14.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:294]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-14.4]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:175]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-15.5]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:61]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:64]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:66]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:158]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:213]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:233]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:274]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:276]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:281]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:283]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:288]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:290]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:295]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:297]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:342]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:348]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-17.1]
[/mnt/d/WorkSpace/MISRA-C_Check/target/sample.c:43]: (style) JP:ここにMISRA-C 2012の文を載せてください [misra-c2012-21.6]

MISRA rule violations found: 67


d:\WorkSpace\MISRA-C_Check>del d:\WorkSpace\MISRA-C_Check\target\sample.c.dump

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
