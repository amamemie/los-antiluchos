// Mantiene las posiciones
struct Node {
    int val , pri , sz ;
    Node *l , *r;
    Node ( int v) {
        val = v;
        pri = rand () ;
        sz = 1;
        l = r = nullptr ;
    }
};
using pnode = Node *;
int sz ( pnode t) {
    return t ? t -> sz : 0;
}
void upd (pnode t) {
    if (t) t -> sz = 1 + sz (t -> l) + sz (t -> r);
}
void split ( pnode t , pnode &l , pnode &r , int k) {
    if (! t) {
        l = r = nullptr ;
        return ;
    }
    int leftSize = sz (t -> l);
    if ( leftSize >= k) {
        split (t -> l , l , t ->l , k) ;
        r = t;
    }
    else {
        split (t -> r , t ->r , r , k - leftSize - 1) ;
        l = t;
    }
    upd (t);
}
pnode merge ( pnode l , pnode r) {
    if (! l || !r ) return l ? l : r;

    if (l -> pri > r -> pri ) {
        l -> r = merge (l -> r , r);
        upd (l );
        return l;
    }
    else {
        r -> l = merge (l , r ->l );
        upd (r );
        return r;
    }
}
void insert ( pnode & root , int pos , int val ) {
    pnode a , b;
    split ( root , a , b , pos );
    root = merge ( merge (a , new Node ( val )) , b) ;
}
void erase ( pnode & root , int pos ) {
    pnode a , b , c;
    split ( root , a , b , pos );
    split (b , b , c , 1) ;
    root = merge (a , c) ;
}
void print(pnode t) {
    if (!t) return;

    print(t->l);
    cout << t->val << " ";
    print(t->r);
}
int get(pnode t, int k) {
    if (!t) return -1;

    int leftSize = sz(t->l);

    if (k < leftSize)
        return get(t->l, k);

    if (k == leftSize)
        return t->val;

    return get(t->r, k - leftSize - 1);
}
