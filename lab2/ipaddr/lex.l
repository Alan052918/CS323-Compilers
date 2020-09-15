%{
    int indicator = 0;
    char *addr_type = NULL;
%}
%option noyywrap

v4seg [0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5]
v4    ^{v4seg}\.{v4seg}\.{v4seg}\.{v4seg}$
v6seg [a-fA-F0-9]{1,4}
v6    ^{v6seg}:{v6seg}:{v6seg}:{v6seg}:{v6seg}:{v6seg}:{v6seg}:{v6seg}$

%%
{v4} { indicator = 4; }
{v6} { indicator = 6; }
<<EOF>> {
    if(indicator == 4)
        addr_type = "IPv4";
    else if(indicator == 6)
        addr_type = "IPv6";
    else
        addr_type = "Neither";
    indicator = 0;
    return 0;
}
\n {}
. {}
%%
char *validIPAddress(char *IP){
    YY_BUFFER_STATE buf;
    buf = yy_scan_string(IP);
    yylex();
    yy_delete_buffer(buf);
    return addr_type;
}
