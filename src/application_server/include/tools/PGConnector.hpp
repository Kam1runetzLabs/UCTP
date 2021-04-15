#ifndef INCLUDE_PGCONNECTOR_HPP_
#define INCLUDE_PGCONNECTOR_HPP_

class PGConnector : public AbstractDBConnector {
 public:
  PGConnector(std::string host, int port, std::string dbname, std::string pass);
  ~PGConnector();
  DBContext Execute(std::string query) override;
};

#endif  // INCLUDE_PGCONNECTOR_HPP_
