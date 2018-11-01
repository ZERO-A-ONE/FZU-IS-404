symbols = 'gT% <RiySk3?fegfefq#2g'
symbols_asc = []
symbols_list = []
i = 0
listlen = len(symbols)
sylen = len(symbols)
for i  in  symbols:
    symbols_asc.append(ord(i))
for x in range(listlen):
    symbols_list.append(ord(symbols[x]))
print(symbols_asc)
print(symbols_list)