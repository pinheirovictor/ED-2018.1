package br.com.ufc.util;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.security.core.Authentication;
import org.springframework.security.web.authentication.logout.LogoutSuccessHandler;

import br.com.ufc.controller.PedidoController;


public class MyLogoutSuccessHandle implements LogoutSuccessHandler {
	@Override
	public void onLogoutSuccess(HttpServletRequest request, HttpServletResponse response, Authentication authentication)
			throws IOException, ServletException {
		PedidoController.limparCarrinho();
		String URL = "http://localhost:8080/outback/paginainicial";
		response.sendRedirect(URL);
	}
}
