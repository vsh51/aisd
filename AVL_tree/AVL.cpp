#include <iostream>

template <typename T>
class AVL_tree {
private:    
    enum Balance {Lefter=-1, Equal, Righter};

    struct node {
        T key;
        size_t count;
        Balance bal;
        node *left, *right;

        node(T key = T(), node* left = nullptr, node* right = nullptr):
            key(key), count(1), bal(Equal), left(left), right(right) {};
    };

    node* root;

    void insertRec(node*& tree, T key, bool& rise) {
        if (tree == nullptr) {
            // ключ не знайшли, додаємо вершину в дерево, дерево "росте"

            tree = new node(key);
            rise = true;
        }
        else if (tree->key == key) {
            // дерево вже містить ключ, збільшуємо лічильник вершини дерева

            ++tree->count;
        }
        else if (key < tree->key) {
            // ключ міг би знаходитись в лівому піддереві

            insertRec(tree->left, key, rise);

            if (rise) {
                // якщо відбулась вставка, потрібно робити балансування

                switch (tree->bal) {
                    case Righter:
                        // вузол стає збалансованим

                        tree->bal = Equal;
                        rise = false;
                        break;

                    case Equal:
                        // відбувається розбалансування, різниця висот піддерев стає 1
                        // балансування не потрібне з означення АВЛ дерева

                        tree->bal = Lefter;
                        break;

                    case Lefter:
                        // відбувається розбалансування, яке потрібно виправити

                        node* p = tree->left;
                        if (p->bal = Lefter) {
                            // розбалансоване ліве (зовнішнє піддерево, потрібен один обмін) LL

                            tree->left = p->right;
                            p->right = tree;
                            tree->bal = Equal;
                            tree = p;
                        }
                        else {
                            // розбалансоване праве (внутрішнє піддерево, потрібно два обміни) LR

                            node* q = p->right;
                            p->right = q->left;
                            q->left = p;
                            tree->left = q->right;
                            q->right = tree;
                            tree->bal = (q->bal == Lefter) ? Righter : Equal;
                            p->bal = (q->bal == Righter) ? Lefter : Equal;
                            tree = q;
                        }
                        tree->bal = Equal;
                        rise = false;
                        break;
                }
            }
        }
        else {
            // ключ може знаходитись в правому піддереві

            insertRec(tree->right, key, rise);
            if (rise) {
                switch (tree->bal) {
                    case Lefter:
                        tree->bal = Equal;
                        rise = false;
                        break;

                    case Equal:
                        tree->bal = Righter;
                        break;
                    
                    case Righter:
                        node* p = tree->right;

                        if (p->bal == Righter) {
                            // праве (зовнішє) піддерево RR

                            tree->right = p->left;
                            p->left = tree;
                            tree->bal = Equal;
                            tree = p;
                        }
                        else {
                            // ліве (внутрішнє) піддерево RL

                            node* q = p->left;
                            p->left = q->right;
                            q->right = p;
                            tree->right = q->left;
                            q->left = tree;
                            tree->bal = (q->bal == Righter) ? Lefter : Equal;
                            p->bal = (q->bal == Lefter) ? Righter : Equal;
                            tree = q;
                        }
                        tree->bal = Equal;
                        rise = false;
                        break;
                }
            }
        }
    }

    void balanceL(node*& tree, bool& diminish) {
        switch (tree->bal) {
            case Lefter:
                tree->bal = Equal;
                break;

            case Equal:
                tree->bal = Righter;
                diminish = false;
                break;

            case Righter:
                node* p = tree->right;
                Balance bp = p->bal;

                if (bp >= Equal) {
                    tree->right = p->left;
                    p->left = tree;
                    if (bp == Equal) {
                        tree->bal = Righter;
                        p->bal = Lefter;
                        diminish = false;
                    }
                    else {
                        tree->bal = Equal;
                        p->bal = Equal;
                    }
                    tree = p;
                }
                else {
                    node* q = p->left;
                    Balance bq = q->bal;

                    p->left = q->right;
                    q->right = p;
                    tree->right = q->left;
                    q->left = tree;
                    tree->bal = (bq == Righter) ? Lefter : Equal;
                    p->bal = (bq == Lefter) ? Righter : Equal;
                    tree = q;
                    q->bal = Equal;
                }
                break;
        }
    }

    void balanceR(node*& tree, bool& diminish) {
        switch (tree->bal) {
            case Righter:
                tree->bal = Equal;
                break;

            case Equal:
                tree->bal = Lefter;
                diminish = false;
                break;

            case Lefter:
                node* p = tree->left;
                Balance bp = p->bal;

                if (bp <= Equal) {
                    tree->left = p->right;
                    p->right = tree;
                    if (bp == Equal) {
                        tree->bal = Lefter;
                        p->bal = Righter;
                        diminish = false;
                    }
                    else {
                        tree->bal = Equal;
                        p->bal = Equal;
                    }
                    tree = p;
                }
                else {
                    node* q = p->right;
                    Balance bq = q->bal;

                    p->right = q->left;
                    q->left = p;
                    tree->left = q->right;
                    q->right = tree;
                    tree->bal = (bq == Lefter) ? Righter : Equal;
                    p->bal = (bq == Righter) ? Lefter : Equal;
                    tree = q;
                    q->bal = Equal;
                }
                break;
        }
    }

    node* toDel;
    void delLast(node*& r, bool& diminish) {
        if (r->right != nullptr) {
            delLast(r->right, diminish);
            if (diminish) balanceR(r, diminish);
        }
        else {
            toDel->key = r->key;
            toDel->count = r->count;
            toDel = r;
            r = r->left;
            diminish = true;
        }
    }
    bool widthdrawRec(node*& tree, T key, bool& diminish) {
        if (tree == nullptr) {
            return false;
        }
        else if(key < tree->key) {
            bool result = widthdrawRec(tree->left, key, diminish);
            if (diminish) balanceL(tree, diminish);
            return result;
        }
        else if (key > tree->key) {
            bool result = widthdrawRec(tree->right, key, diminish);
            if (diminish) balanceR(tree, diminish);
            return result;
        }
        else {
            toDel = tree;
            if (toDel->count > 1) {
                --toDel->count;
                return true;
            }
            if (toDel->right == nullptr) {
                tree = toDel->left;
                diminish = true;
            }
            else if (toDel->right == nullptr) {
                tree = toDel->right;
                diminish = true;
            }
            else {
                delLast(tree->left, diminish);
                if (diminish) balanceL(tree, diminish);
            }
            delete toDel;
            return true;
        }
    }

    void printWithShift(node* tree, std::ostream& os, int shift) {
        if (tree->right != nullptr) printWithShift(tree->right, os, shift + 5);
        for (int i = 0; i < shift; ++i) os << ' ';
        os << tree->key << ":" << tree->count << "\n";
        if (tree->left != nullptr) printWithShift(tree->left, os, shift + 5);
    }

public:
    typedef T data_type;

    AVL_tree() {
        root = nullptr; 
    }

    void insert(T key) {
        if (root == nullptr) root = new node(key);
        else {
            bool rise = false;
            insertRec(root, key, rise);
        }
    }

    bool delete_key(T key) {
        if (root == nullptr) return 0;
        else {
            bool diminish = false;
            return widthdrawRec(root, key, diminish);
        }
    }

    void printOn(std::ostream& os) {
        if (root == nullptr) {
            os << "\n";
        }
        else printWithShift(root, os, 0);
    }

    size_t count(T key) {
        node* p = root;
        while (p != nullptr) {
            if (key < p->key) p = p->left;
            else if (key > p->key) p = p->right;
            else return p->count;
        }
        return 0;
    }

    void set_count(T key, size_t count) {
        if (count < 1) {
            return;
        }
        node* p = root;
        while (p != nullptr) {
            if (key < p->key) p = p->left;
            else if (key > p->key) p = p->right;
            else {
                p->count = count;
                return;
            }
        } 
    }
};