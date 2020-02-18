# Uls
The recode of a standard mac Os ls command.

# Implemented Flags
- A, C, F, G, R, S, a, c, f, g, l, o, r, s, u, 1

# Bugs
- Writing to a file with the -C flag due to spaces instead of tabs. 
- Flag -F don't write *. 
- Does not display an error "Permission denied" with folders updated with command chmod. 
