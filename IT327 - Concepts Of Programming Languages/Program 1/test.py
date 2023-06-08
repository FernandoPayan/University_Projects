import re

the_string = "Take 1st item"
print(the_string)

x = re.search(r"(?:\b\d+(?:[st]{2}|[nd]{2}|[rd]{2}|[th]{2})\b)", the_string)

first_part = the_string[:x.start()]
last_part = the_string[x.end():]

print(first_part)
print(last_part)

test = the_string[:x.start()]
test += "first"
test += the_string[x.end():]
print(test)
