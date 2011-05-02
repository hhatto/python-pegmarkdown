import pegmarkdown

mdtext = open('test.markdown').read()
print pegmarkdown.markdown(mdtext)
