#include <iostream>
#include <cstdio>

struct CNode {
    int Key;
    int Height;
    CNode* Left;
    CNode* Right;

    CNode(int key = 0) : Key(key), Height(1), Left(0), Right(0) {}
};

int Height(CNode* node) {
    return node == 0 ? 0 : node->Height;
}

int BalanceFactor(CNode* node)
{
    return Height(node->Right) - Height(node->Left);
}

void FixHeight(CNode* p) {
    int hl = Height(p->Left);
    int hr = Height(p->Right);
    p->Height = (hl>hr?hl:hr)+1;
}

CNode* RotateRight(CNode* p) {
    CNode* q = p->Left;
    p->Left = q->Right;
    q->Right = p;
    FixHeight(p);
    FixHeight(q);
    return q;
}

CNode* RotateLeft(CNode* p) {
    CNode* q = p->Right;
    p->Right = q->Left;
    q->Left = p;
    FixHeight(p);
    FixHeight(q);
    return q;
}

CNode* Balance(CNode* p) {
    FixHeight(p);
    if( BalanceFactor(p)==2 )
    {
        if( BalanceFactor(p->Right) < 0 )
            p->Right = RotateRight(p->Right);
        return RotateLeft(p);
    }
    if( BalanceFactor(p)==-2 )
    {
        if( BalanceFactor(p->Left) > 0  )
            p->Left = RotateLeft(p->Left);
        return RotateRight(p);
    }
    return p;
}

CNode* Insert(CNode* p, int key) {
    if( p == 0 )
                return new CNode(key);
    if( key < p->Key )
        p->Left = Insert(p->Left, key);
    else
        p->Right = Insert(p->Right, key);
    return Balance(p);
}

CNode* FindMin(CNode* p) {
    return p->Left == 0 ? p : FindMin(p->Left);
}

CNode* RemoveMin(CNode* p) {
    if( p->Left == 0 )
        return p->Right;
    p->Left = RemoveMin(p->Left);
    return Balance(p);
}

CNode* Remove(CNode* p, int key) {
    if( p == 0 ) return 0;
        if( key == p->Key ) {
        CNode* left = p->Left;
        CNode* right = p->Right;
        delete p;
        if( right == 0 ) return left;
        CNode* min = FindMin(right);
        min->Right = RemoveMin(right);
        min->Left = left;
        return Balance(min);
    }
    if( key < p->Key )
        p->Left = Remove(p->Left, key);
    else
        p->Right = Remove(p->Right, key);
    return Balance(p);
}

void Delete(CNode* node) {
    if (!node) return;
    Delete(node->Left);
    Delete(node->Right);
    delete node;
}

int main() {

        CNode* root = 0;

        while( true ) {
                int key = 0;
                std::cin >> key;
                if( std::cin.eof() ) {
                        break;
                }
                if( key >= 0 ) {
                        root = Insert(root, key);
                } else {
                        root = Remove(root, -key);
                }
        }

        std::cout << Height(root);

        Delete(root);

        return 0;
}
