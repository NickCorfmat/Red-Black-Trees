// --------------------------------------------------------------
// Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa8
// --------------------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>

#include "Dictionary.h"

const int BLACK = 0;
const int RED = 1;

/*** Constructors-Destructors ***/

Dictionary::Node::Node(keyType k, valType v) {
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	color = 1;
}

Dictionary::Dictionary() {
        nil = new Node("-1", -1);
        nil->color = 0;
        root = nil;
        root->parent = nil;
        root->left = nil;
        root->right = nil;
        current = root;
        num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) {
        nil = new Node("-1", -1);
        nil->color = 0;
        root = nil;
        root->parent = nil;
        root->left = nil;
        root->right = nil;
        current = root;
        num_pairs = 0;

        preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary() {
        postOrderDelete(root);
        delete nil;
}

/*** Helper Functions ***/

void Dictionary::inOrderString(std::string& s, Node* R) const {
	if (R != nil) {
		inOrderString(s, R->left);
		s += R->key + " : " + std::to_string(R->val) + "\n";
		inOrderString(s, R->right);
	}
}

void Dictionary::preOrderString(std::string& s, Node* R) const {
	if (R != nil) {
		s += R->key + (R->color==0?"\n":" (RED)\n");
		preOrderString(s, R->left);
		preOrderString(s, R->right);
	}
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
	if (R != N) {
		setValue(R->key, R->val);
		preOrderCopy(R->left, N);
		preOrderCopy(R->right, N);
	}
}

void Dictionary::postOrderDelete(Node* R) {
	if (R != nil) {
		postOrderDelete(R->left);
		postOrderDelete(R->right);
		delete R;
	}
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
	while (R != nil && R->key != k) {
		if (k < R->key) {
			R = R->left;
		} else {
			R = R->right;
		}
	}

	return R;
}

Dictionary::Node* Dictionary::findMin(Node* R) {
	if (R != nil) {
		while (R->left != nil) {
			R = R->left;
		}
	}

	return R;
}

Dictionary::Node* Dictionary::findMax(Node* R) {
	if (R != nil) {
        	while (R->right != nil) {
                	R = R->right;
        	}
	}

        return R;
}

Dictionary::Node* Dictionary::findNext(Node* N) {
	if (N->right != nil) {
		return findMin(N->right);
	}

	Node* y = N->parent;

	while (y != nil && N == y->right) {
		N = y;
		y = y->parent;
	}

	return y;
}

Dictionary::Node* Dictionary::findPrev(Node* N) {
	if (N->left != nil) {
                return findMax(N->left);
        }

        Node* y = N->parent;

        while (y != nil && N == y->left) {
                N = y;
                y = y->parent;
        }

        return y;
}

/*** RBT Helper Functions ***/

void Dictionary::LeftRotate(Node* N) {
	Node* y = N->right;

        N->right = y->left;

        if (y->left != nil) {
                y->left->parent = N;
        }

        y->parent = N->parent;

        if (N->parent == nil) {
                root = y;
        } else if (N == N->parent->left) {
                N->parent->left = y;
        } else {
                N->parent->right = y;
        }

        y->left = N;
        N->parent = y;
}

void Dictionary::RightRotate(Node* N) {
	Node* y = N->left;

	N->left = y->right;

	if (y->right != nil) {
		y->right->parent = N;
	}

	y->parent = N->parent;

	if (N->parent == nil) {
		root = y;
	} else if (N == N->parent->right) {
		N->parent->right = y;
	} else {
		N->parent->left = y;
	}

	y->right = N;
	N->parent = y;
}

void Dictionary::RB_InsertFixUp(Node* N) {
	Node* y;

	while (N->parent->color == RED) {
		if (N->parent == N->parent->parent->left) {
			y = N->parent->parent->right;
         
			if (y->color == RED) {
				N->parent->color = BLACK;
				y->color = BLACK;
				N->parent->parent->color = RED;
				N = N->parent->parent;
			} else {
				if (N == N->parent->right) {
					N = N->parent;
					LeftRotate(N);
				}
				
				N->parent->color = BLACK;
				N->parent->parent->color = RED;
				RightRotate(N->parent->parent);
			}
		} else {
			y = N->parent->parent->left;
			
			if (y->color == RED) {
				N->parent->color = BLACK;
				y->color = BLACK;
				N->parent->parent->color = RED;
				N = N->parent->parent;
			} else {
				if (N == N->parent->left) {
					N = N->parent;
					RightRotate(N);
				}
				
				N->parent->color = BLACK;
				N->parent->parent->color = RED;
				LeftRotate(N->parent->parent);
			}
		}
	}
	
	root->color = BLACK;
}

void Dictionary::RB_Transplant(Node* u, Node* v) {
	if (u->parent == nil) {
		root = v;
	} else if (u == u->parent->left) {
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}

	v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* N) {
	while (N != root && N->color == BLACK) {
		if (N == N->parent->left) {
			Node* w = N->parent->right;

			if (w->color == RED) {
				w->color = BLACK;
				N->parent->color = RED;
				LeftRotate(N->parent);
				w = N->parent->right;
			}

			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				N = N->parent;
			} else {
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					RightRotate(w);
					w = N->parent->right;
				}

				w->color = N->parent->color;
				N->parent->color = BLACK;
				w->right->color = BLACK;
				LeftRotate(N->parent);
				N = root;
			}
		} else {
			Node* w = N->parent->left;

			if (w->color == RED) {
				w->color = BLACK;
				N->parent->color = RED;
				RightRotate(N->parent);
				w = N->parent->left;
			}

			if (w->right->color == BLACK && w->left->color == BLACK) {
				w->color = RED;
				N = N->parent;
			} else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					LeftRotate(w);
					w = N->parent->left;
				}

				w->color = N->parent->color;
				N->parent->color = BLACK;
				w->left->color = BLACK;
				RightRotate(N->parent);
				N = root;
			}
		}
	}

	N->color = BLACK;
}

void Dictionary::RB_Delete(Node* N) {
        Node* y = N;
	Node* x;

        int y_original_color = y->color;

        if (N->left == nil) {
                x = N->right;
                RB_Transplant(N, N->right);
        } else if (N->right == nil) {
                x = N->left;
                RB_Transplant(N, N->left);
        } else {
                y = findMin(N->right);
                y_original_color = y->color;
                x = y->right;

                if (y->parent == N) {
                        x->parent = y;
                } else {
                        RB_Transplant(y, y->right);
                        y->right = N->right;
                        y->right->parent = y;
                }

                RB_Transplant(N, y);
                y->left = N->left;
                y->left->parent = y;
                y->color = N->color;
        }

        if (y_original_color == BLACK) {
                RB_DeleteFixUp(x);
        }
}

/*** Access Functions ***/

int Dictionary::size() const {
	return num_pairs;
}

bool Dictionary::contains(keyType k) const {
	Node* N = search(root, k);

	return N != nil;
}

valType& Dictionary::getValue(keyType k) const {
	if (!contains(k)) {
		throw std::invalid_argument("Error: calling getValue() on invalid key");
	}

	Node* N = search(root, k);

	return N->val;
}

bool Dictionary::hasCurrent() const {
	return current != nil;
}

keyType Dictionary::currentKey() const {
	if (!hasCurrent()) {
                throw std::invalid_argument("Error: calling currentKey() on non-existent current iterator");
        }

	return current->key;
}

valType& Dictionary::currentVal() const {
	if (!hasCurrent()) {
                throw std::invalid_argument("Error: calling currentVal() on non-existent current iterator");
        }

	return current->val;
}

/*** Manipulation Procedures ***/

void Dictionary::clear() {
	postOrderDelete(root);
	root = nil;
	current = nil;
	num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v) {
	Node* z = new Node(k, v);
	Node* y = nil;
	Node* x = root;

	z->parent = nil;
	z->left = nil;
	z->right = nil;

	while (x != nil) {
		y = x;

		if (z->key < x->key) {
			x = x->left;
		} else {
			x = x->right;
		}
	}

	z->parent = y;

	if (y == nil) {
		root = z;
	} else if (y->key == k) {
		y->val = v;
		delete z;
		return;	
	} else if (z->key < y->key) {
		y->left = z;
	} else {
		y->right = z;
	}

	z->left = nil;
	z->right = nil;
	z->color = RED;

	num_pairs++;
	RB_InsertFixUp(z);
}

void Dictionary::remove(keyType k) {
	if (!contains(k)) {
		throw std::invalid_argument("Error: Calling remove() on non-existent key");
	}

	Node* N = search(root, k);
	
	if (N == current) {
		current = nil;
	}

	RB_Delete(N);
	num_pairs--;

	delete N;
}

void Dictionary::begin() {
	if (root != nil) {
		current = findMin(root);
	}
}

void Dictionary::end() {
	if (root != nil) {
		current = findMax(root);
	}
}

void Dictionary::next() {
	if (!hasCurrent()) {
                throw std::invalid_argument("Error: calling next() on non-existent current iterator");
        }
	
	current = findNext(current);
}

void Dictionary::prev() {
	if (!hasCurrent()) {
                throw std::invalid_argument("Error: calling prev() on non-existent current iterator");
        }

	current = findPrev(current);
}

/*** Other Functions ***/

std::string Dictionary::to_string() const {
	std::string s;
	inOrderString(s, root);
	return s;
}

std::string Dictionary::pre_string() const {
	std::string s;
	preOrderString(s, root);
	return s;
}

bool Dictionary::equals(const Dictionary& D) const {
	if (num_pairs != D.num_pairs) {
		return false;
	}

	std::string A = to_string();
	std::string B = D.to_string();

	return A == B;
}

/*** Overload Operators ***/

std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
	return stream << D.to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B ) {
	return A.equals(B);
}

Dictionary& Dictionary::operator=( const Dictionary& D ) {
	if (this != &D) {
		Dictionary temp = D;

		std::swap(nil, temp.nil);
		std::swap(root, temp.root);
		std::swap(current, temp.current);
		std::swap(num_pairs, temp.num_pairs);
	}

	return *this;
}
