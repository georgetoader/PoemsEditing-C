# poems  
  Pentru citire am folosit functia oferita in biblioteca static "load" in functie de parametrul primit la input si folosing strstr.
### TASK 1(uppercase)
  Am parcurs intreaga poezie si la gasirea fiecarei litere am verificat daca era majuscula si daca da am schimbat-o. Pentru asta am folosit functiile implementate de mine "isLowerCase", "isUpperCase", "isLetter", "change".
### TASK 2(trimming)
  Parcurg toata poezia si elimin caracterele non-litera dintre cuvinte iar in locul lor las un singur ' ' si apoi caracterul de dupa ultimul cuvant daca exista.
### TASK 3(silly)
  Am parcurs poezia si pe fiecare litera o schimbam conform cerintei.
### TASK 4(friendly)
  Am gasit coordonatele fiecarui cuvant in poezie si am apelat functia "get_friendly_word" pentru a vedea daca are diminutiv sau nu. In caz afirmativ am schimbat acel cuvant cu sinonimul lui folosing "memcpy" intr-o copie a matricei originale pe care apoi am reatribuit-o prin "strcpy".
### TASK 5(rhyme)
  Am separat poezia pe versuri si am gasit atat coordonatele de inceput ale ultimului cuvant din fiecare vers in "v[i]", cat si cuvantul in sine pe care l-am stocat in "word[i]". Pe acest cuvant am folosit "uppercase" pentru a nu avea probleme cu litera mica sau majuscula. Variabila "total_car" am folosit-o pentru a tine minte cate caractere am parcurs pana la acel vers din poezie. Daca am ajuns la ultimul vers din catren, adica versul 4, in functie de ce rima trebuie sa fac initializez variabilele corespunzatoare si apoi apelez functia "get_synonym" pentru acele ultime cuvinte stocate anterior in cazul in care cuvintele originale nu rimeaza. Cum in cerinta specifica ca cele 2 cuvinte nu pot fi modificate in acelasi timp nu verific daca amandoua returneaza nenul. Pentru cuvantul care returneaza o lista de sinonime aleg cel mai bun cuvant lexicografic care rimeaza dintre acestea si il pun in locul cuvantului original cu ajutorul functiei "swap_words". Daca noul cuvant difera in lungime fata de cuvantul original atunci modific vectorul cu cele 4 variabile ce contin coordonatele celor 4 cuvinte, altfel putand sa avem probleme cu urmatoarele 2 versuri. Dupa ce termin cu prima rima o fac si pe a doua.
