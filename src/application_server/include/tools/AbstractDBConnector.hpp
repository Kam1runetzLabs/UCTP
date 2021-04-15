#ifndef INCLUDE_ABSTRACTDBCONNECTOR_HPP_
#define INCLUDE_ABSTRACTDBCONNECTOR_HPP_

class AbstractDBConnector {
 public:
  virtual AbstractDBConnector(std::string host, int port, std::string dbname, std::string pass);
  virtual ~AbstractDBConnector();
  virtual DBContext Execute(std::string query) = 0;
 private:
  std::string m_Host;
  int m_Port;
  std::string m_Name;
  std::string m_User;
  std::string m_Pass;
  virtual void Connect() = 0;
};

#endif  // INCLUDE_ABSTRACTDBCONNECTOR_HPP_
