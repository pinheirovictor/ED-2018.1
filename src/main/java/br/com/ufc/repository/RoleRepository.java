package br.com.ufc.repository;

import org.springframework.data.jpa.repository.JpaRepository;

import br.com.ufc.model.Role;

public interface RoleRepository extends JpaRepository<Role, String> {

}
