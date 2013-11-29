#include <iostream>
#include <cstdio>

struct CNode {
    int Key;
    int Height;
    int NodeNumber;
    CNode* Left;
    CNode* Right;

    CNode(int key = 0) : Key(key), Height(1), NodeNumber(1), Left(0), Right(0) {}
};

int Height(CNode* node) {
    return node == 0 ? 0 : node->Height;
}

int NodeNumber(CNode* node) {
    return node == 0 ? 0 : node->NodeNumber;
}

int BalanceFactor(CNode* node)
{
    return Height(node->Right) - Height(node->Left);
}

void FixHeight(CNode* p) {
    int hl = Height(p->Left);
    int hr = Height(p->Right);
    p->Height = (hl > hr ? hl : hr) + 1;
    p->NodeNumber = NodeNumber(p->Left) + NodeNumber(p->Right) + 1;
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

CNode* Insert(CNode* p, int key, int position) {
    if( p == 0 ) {
        printf("%d\n", position);
        return new CNode(key);
    }
    if( key < p->Key ) {
        position += NodeNumber(p->Right) + 1;
        p->Left = Insert(p->Left, key, position);
    }
    else {
        p->Right = Insert(p->Right, key, position);
    }
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

CNode* Remove(CNode* p, int pos) {
    if( p == 0 || pos > NodeNumber(p)) return 0;

    int temp = NodeNumber(p->Right) + 1;

    if( pos == temp ) {
        CNode* left = p->Left;
        CNode* right = p->Right;
        delete p;

        if( right == 0 ) return left;

        CNode* min = FindMin(right);
        min->Right = RemoveMin(right);
        min->Left = left;
        return Balance(min);
    }
    if( pos < temp )
        p->Right = Remove(p->Right, pos);
    else
        p->Left = Remove(p->Left, pos - temp);
    return Balance(p);
}

/*CNode* Remove(CNode* _root, int _num) {
    if (_root == 0 || _num > NodeNumber(_root))
         return 0;

    int cur = NodeNumber(_root->Right) + 1;

    if (_num == cur) {
        CNode* l = _root->Left;
        CNode* r = _root->Right;
        delete _root;

        if (r == 0)
            return l;

        CNode* min = FindMin(r);
        min->Right = RemoveMin(r);
        min->Left = l;

        return Balance(min);
    }
    else if (_num < cur)
        _root->Right = Remove(_root->Right, _num);
    else
        _root->Left = Remove(_root->Left, _num - cur);

    return Balance(_root);
}*/

void Delete(CNode* node) {
    if (!node) return;
    Delete(node->Left);
    Delete(node->Right);
    delete node;
}

int main() {
    CNode* root = 0;
    int N = 0;
    std::cin >> N;
    for (int i = 0; i < N; ++i) {
            int key = 0;
            int a = 0;
            std::cin >> a >> key;

            if( a == 1 ) {
                    root = Insert(root, key, 0);
            } else {
                    root = Remove(root, key + 1);
            }
    }

    Delete(root);

    return 0;
}

