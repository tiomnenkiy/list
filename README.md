# list
Template of list &amp; list of lists
/*
 * CList<CListRemoveIfOddValue>
 * не использует конструктор копирования из list.h => если дублирует при выходе будет segfault
 * не правильно дублирует хвостовой элемент (херит оригинал) ..(fixed only for 1-element CList with Copy() from "list.h")
 * если 2 раза использовать dublicate на списке списков размера 1 из элемента 1->2->NULL, будет double free
 */
