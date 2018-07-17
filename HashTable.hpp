class Hash_Table {
private:
	unsigned int hash_value;
	static unsigned int hash_count;

public:
	Hash_Table();
	unsigned int hash() const;
};

unsigned int Hash_Table::hash_count = 0;

Hash_Table::Hash_Table() {
	hash_value = hash_count;
	hash_count++;
}

unsigned int Hash_Table::hash() const{
  return hash_value;
}
