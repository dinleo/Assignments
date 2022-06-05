
#include "AVLTree.h"
#include "LinkedBinaryTree.h"

//
// Implementation
//
template<typename E>
// constructor
AVLTree<E>::AVLTree() : ST() {}

template<typename E>
// node height utility
int AVLTree<E>::height(const TPos &v) const { return (v.isExternal() ? 0 : (*v).height()); }

template<typename E>
// set height utility
void AVLTree<E>::setHeight(TPos v) {
    int hl = height(v.left());
    int hr = height(v.right());
    (*v).setHeight(1 + std::max(hl, hr));            // max of left & right
}

template<typename E>
// is v balanced?
bool AVLTree<E>::isBalanced(const TPos &v) const {
    int bal = height(v.left()) - height(v.right());
    return ((-1 <= bal) && (bal <= 1));
}

template<typename E>
// get tallest grandchild
typename AVLTree<E>::TPos AVLTree<E>::tallGrandchild(const TPos &z) const {
    TPos zl = z.left();
    TPos zr = z.right();
    if (height(zl) >= height(zr))            // left child taller
        if (height(zl.left()) >= height(zl.right()))
            return zl.left();
        else
            return zl.right();
    else                        // right child taller
    if (height(zr.right()) >= height(zr.left()))
        return zr.right();
    else
        return zr.left();
}


//
// ToDo
//

template<typename E>
// remove key k entry
void AVLTree<E>::erase(const K &k) {
    TPos v = ST::finder(k, ST::root());
    if (v.isExternal()) {
        throw "Erase of nonexistent";
    }
    rebalance(eraser(v));
}

template<typename E>
// insert (k,x)
typename AVLTree<E>::Iterator AVLTree<E>::insert(const K &k, const V &x) {
    TPos v = ST::inserter(k, x);
    setHeight(v);
    rebalance(v);
    return Iterator(v);
}

template<typename E>
// rebalancing utility
void AVLTree<E>::rebalance(const TPos &v) {
    TPos temp = v;
    while (!(temp == ST::root())) {
        temp = temp.parent();
        setHeight(temp);
        if (!isBalanced(temp)) {
            TPos x = tallGrandchild(temp);
            temp = restructure(x);
            setHeight(temp.left());
            setHeight(temp.right());
            setHeight(temp);
        }
    }
}

typedef LinkedBinaryTree<AVLEntry<Elem>>::Node* LBTNodeP;
template<typename E>
// Binary Search Tree Rotation
typename AVLTree<E>::TPos AVLTree<E>::restructure(const TPos &v) {
    TPos c = v;
    TPos b = c.parent();
    TPos a = b.parent();
    TPos g = a.parent();

    LBTNodeP gp = g.v;
    LBTNodeP ap = a.v;
    LBTNodeP bp = b.v;
    LBTNodeP cp = c.v;


    K aKey = ap->elt.key();
    K bKey = bp->elt.key();
    K cKey = cp->elt.key();

    // L
    if (bKey < aKey) {
        // LL
        if (cKey < bKey) {
            TPos br = b.right();
            LBTNodeP brp = br.v;
            ap->left = br.v;
            bp->right = a.v;
            ap->par = b.v;
            cp->par = b.v;
            brp->par = a.v;

            if (g.left().v == a.v)
                gp->left = b.v;
            else if (g.right().v == a.v)
                gp->right = b.v;
            else {
                cout << "Restructure Fail";
            }
            return b.v;
        }
            // LR
        else {
            TPos cr = c.right();
            TPos cl = c.left();
            LBTNodeP crp = cr.v;
            LBTNodeP clp = cl.v;
            cp->par = g.v;
            ap->left = cr.v;
            bp->right = cl.v;
            cp->right = a.v;
            cp->left = b.v;
            bp->par = c.v;
            ap->par = c.v;
            crp->par = a.v;
            clp->par = b.v;
            if (g.left().v == a.v)
                gp->left = c.v;
            else if (g.right().v == a.v)
                gp->right = c.v;
            else {
                cout << "Restructure Fail";
            }
            return c.v;
        }
    }
        // R
    else {
        // RR
        if (bKey < cKey) {
            TPos bl = b.left();
            LBTNodeP blp = bl.v;
            bp->par = g.v;
            ap->right = bl.v;
            bp->left = a.v;
            ap->par = b.v;
            cp->par = b.v;
            blp->par = a.v;
            if (g.left().v == a.v)
                gp->left = b.v;
            else if (g.right().v == a.v)
                gp->right = b.v;
            else {
                cout << "Restructure Fail";
            }
            return b;
        }
            // RL
        else {
            TPos cr = c.right();
            TPos cl = c.left();
            LBTNodeP crp = cr.v;
            LBTNodeP clp = cl.v;
            cp->par = g.v;
            ap->right = cl.v;
            bp->left = cr.v;
            cp->left = a.v;
            cp->right = b.v;
            ap->par = c.v;
            bp->par = c.v;
            clp->par = a.v;
            crp->par = b.v;
            if (g.left().v == a.v)
                gp->left = c.v;
            else if (g.right().v == a.v)
                gp->right = c.v;
            else {
                cout << "Restructure Fail";
            }
            return c;
        }
    }
}

