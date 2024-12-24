#pragma once
struct connections {
	int id_entry;
	int id_pipe;
	int id_out;
	friend ostream& operator<<(ostream& os, const connections& conn) {
		os << conn.id_entry << " " << conn.id_pipe << " " << conn.id_out << endl;
		return os;
	}
	friend istream& operator>>(istream& is, connections& conn) {
		is >> conn.id_entry >> conn.id_pipe >> conn.id_out;
		return is;
	}
};