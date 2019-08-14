package br.com.ufc.model;

import java.util.ArrayList;
import java.util.List;

import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.ManyToMany;

import org.springframework.security.core.GrantedAuthority;

@Entity
public class Role implements GrantedAuthority {

	private static final long serialVersionUID = 1L;

	@Id
	private String papel;

	@ManyToMany(mappedBy = "roles")
	private List<Pessoa> usuarios = new ArrayList<Pessoa>();

	@Override
	public String getAuthority() {
		return this.papel;
	}

	public String getpapel() {
		return papel;
	}

	public void setpapel(String papel) {
		this.papel = papel;
	}

	public List<Pessoa> getUsuarios() {
		return usuarios;
	}

	public void setUsuarios(List<Pessoa> usuarios) {
		this.usuarios = usuarios;
	}

}
