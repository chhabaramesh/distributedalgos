// Persistent kv store
class Store {

public:
	virtual get(string &key);
	virtual put(string &key, string &val);
};


class FileStore: public Store {
		string filePath;
public:

		Reinit(string file);
		Open(string file);

		virtual get(string &key);
		virtual put(string &key, string &val);

};


