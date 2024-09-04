public class TestBiblio {
public static void main(String[] args) {
    
    Bibliotheque b=new Bibliotheque();
    Document a= new Livre("harry potter", "rowling", "Bloomsbury");
    Document c= new BandeDessinee("titeuf", "zep", "zep");
    Materiel macbook = new OrdinateurPortable(false, "APPLE",Os.LINUX);
    Adherant artinho=new Adherant("hashani","artinho",Statut.ETUDIANT);
    b.ajouterDocument(a);
    b.ajouterDocument(c);
    b.ajouterMateriel(macbook);
    b.ajouterAdherant(artinho);
}
}
