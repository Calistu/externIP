<h1 align="center">My extern IP</h1>
<p>
with it, you can get easily your extern ip on your terminal or command prompt.
</p>
install using only:<br>
<b>gcc myip.c -o /bin/myip</b> 

tip: you can do a network scan using the quiet mode, the myip ll print your ip,
so you can pass the output to others programs with pipe

ex: nmap \`myip -q\` <br>
ex: ping \`myip -q\` <br>
